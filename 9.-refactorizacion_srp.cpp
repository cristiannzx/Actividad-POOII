#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Usuario {
    int id;
    string nombre;
    string correo;
};
struct Oferta {
    int id;
    string titulo;
    string empresa;
    double salario;
    bool activa;
};
struct Postulacion {
    int idUsuario;
    int idOferta;
};
class Validador {
public:
    bool correoValido(const string& correo) const;
    bool nombreValido(const string& nombre) const;
    bool ofertaValida(const string& titulo, const string& empresa, double salario) const;
};
class RepositorioUsuarios {
private:
    vector<Usuario> usuarios;
    int siguienteId;
public:
    RepositorioUsuarios();
    int agregar(const string& nombre, const string& correo);
    bool existeCorreo(const string& correo) const;
    const Usuario* buscar(int id) const;
    const vector<Usuario>& listar() const;
};
class RepositorioOfertas {
private:
    vector<Oferta> ofertas;
    int siguienteId;
public:
    RepositorioOfertas();
    int agregar(const string& titulo, const string& empresa, double salario);
    void cerrar(int id);
    const Oferta* buscar(int id) const;
    const vector<Oferta>& listar() const;
};
class Notificador {
public:
    void enviarCorreo(const string& destino, const string& mensaje) const;
};
class ServicioPostulaciones {
private:
    const RepositorioUsuarios& usuarios;
    const RepositorioOfertas& ofertas;
    const Notificador& notificador;
    vector<Postulacion> postulaciones;
public:
    ServicioPostulaciones(const RepositorioUsuarios& usuarios, const RepositorioOfertas& ofertas, const Notificador& notificador);
    bool postular(int idUsuario, int idOferta);
    const vector<Postulacion>& listar() const;
};
class GeneradorReportes {
private:
    const RepositorioUsuarios& usuarios;
    const RepositorioOfertas& ofertas;
    const ServicioPostulaciones& postulaciones;
public:
    GeneradorReportes(const RepositorioUsuarios& usuarios, const RepositorioOfertas& ofertas, const ServicioPostulaciones& postulaciones);
    void generar() const;
};
bool Validador::correoValido(const string& correo) const {
    size_t arroba = correo.find('@');
    return arroba != string::npos && arroba > 0 && correo.find('.', arroba) != string::npos;
}
bool Validador::nombreValido(const string& nombre) const {
    return !nombre.empty();
}
bool Validador::ofertaValida(const string& titulo, const string& empresa, double salario) const {
    return !titulo.empty() && !empresa.empty() && salario > 0;
}
RepositorioUsuarios::RepositorioUsuarios() : siguienteId(1) {}
int RepositorioUsuarios::agregar(const string& nombre, const string& correo) {
    usuarios.push_back({siguienteId, nombre, correo});
    return siguienteId++;
}
bool RepositorioUsuarios::existeCorreo(const string& correo) const {
    for (const auto& u : usuarios) {
        if (u.correo == correo) return true;
    }
    return false;
}
const Usuario* RepositorioUsuarios::buscar(int id) const {
    for (const auto& u : usuarios) {
        if (u.id == id) return &u;
    }
    return nullptr;
}
const vector<Usuario>& RepositorioUsuarios::listar() const {
    return usuarios;
}
RepositorioOfertas::RepositorioOfertas() : siguienteId(1) {}
int RepositorioOfertas::agregar(const string& titulo, const string& empresa, double salario) {
    ofertas.push_back({siguienteId, titulo, empresa, salario, true});
    return siguienteId++;
}
void RepositorioOfertas::cerrar(int id) {
    for (auto& o : ofertas) {
        if (o.id == id) o.activa = false;
    }
}
const Oferta* RepositorioOfertas::buscar(int id) const {
    for (const auto& o : ofertas) {
        if (o.id == id) return &o;
    }
    return nullptr;
}
const vector<Oferta>& RepositorioOfertas::listar() const {
    return ofertas;
}
void Notificador::enviarCorreo(const string& destino, const string& mensaje) const {
    cout << "[CORREO a " << destino << "] " << mensaje << "\n";
}
ServicioPostulaciones::ServicioPostulaciones(const RepositorioUsuarios& usuarios, const RepositorioOfertas& ofertas, const Notificador& notificador)
    : usuarios(usuarios), ofertas(ofertas), notificador(notificador) {}

bool ServicioPostulaciones::postular(int idUsuario, int idOferta) {
    const Usuario* usuario = usuarios.buscar(idUsuario);
    const Oferta* oferta = ofertas.buscar(idOferta);
    if (!usuario || !oferta || !oferta->activa) return false;
    for (const auto& p : postulaciones) {
        if (p.idUsuario == idUsuario && p.idOferta == idOferta) return false;
    }
    postulaciones.push_back({idUsuario, idOferta});
    notificador.enviarCorreo(usuario->correo, "Tu postulacion a '" + oferta->titulo + "' fue registrada");
    return true;
}
const vector<Postulacion>& ServicioPostulaciones::listar() const {
    return postulaciones;
}

GeneradorReportes::GeneradorReportes(const RepositorioUsuarios& usuarios, const RepositorioOfertas& ofertas, const ServicioPostulaciones& postulaciones)
    : usuarios(usuarios), ofertas(ofertas), postulaciones(postulaciones) {}

void GeneradorReportes::generar() const {
    cout << "\n===== REPORTE DEL PORTAL =====\n";
    cout << "Usuarios: " << usuarios.listar().size() << " | Ofertas: " << ofertas.listar().size()
              << " | Postulaciones: " << postulaciones.listar().size() << "\n";
    for (const auto& o : ofertas.listar()) {
        cout << "- " << o.titulo << " (" << o.empresa << ", S/ " << o.salario << ", "
                  << (o.activa ? "activa" : "cerrada") << ")\n";
        for (const auto& p : postulaciones.listar()) {
            if (p.idOferta != o.id) continue;
            const Usuario* u = usuarios.buscar(p.idUsuario);
            if (u) cout << "    * " << u->nombre << "\n";
        }
    }
}
int registrarUsuario(const Validador& validador, RepositorioUsuarios& repo, const Notificador& notificador,
                     const string& nombre, const string& correo) {
    if (!validador.nombreValido(nombre) || !validador.correoValido(correo) || repo.existeCorreo(correo)) return -1;
    int id = repo.agregar(nombre, correo);
    notificador.enviarCorreo(correo, "Bienvenido al portal, " + nombre);
    return id;
}
int publicarOferta(const Validador& validador, RepositorioOfertas& repo,
                   const string& titulo, const string& empresa, double salario) {
    if (!validador.ofertaValida(titulo, empresa, salario)) return -1;
    return repo.agregar(titulo, empresa, salario);
}
int main() {
    Validador validador;
    Notificador notificador;
    RepositorioUsuarios usuarios;
    RepositorioOfertas ofertas;
    ServicioPostulaciones postulaciones(usuarios, ofertas, notificador);
    GeneradorReportes reportes(usuarios, ofertas, postulaciones);

    int ana = registrarUsuario(validador, usuarios, notificador, "Ana Torres", "ana@correo.com");
    int luis = registrarUsuario(validador, usuarios, notificador, "Luis Quispe", "luis@correo.com");
    int invalido = registrarUsuario(validador, usuarios, notificador, "Sin Correo", "correo-malo");
    cout << "Registro con correo invalido devuelve: " << invalido << "\n\n";

    int oferta1 = publicarOferta(validador, ofertas, "Desarrollador C++", "TechPuno", 3500.0);
    int oferta2 = publicarOferta(validador, ofertas, "Analista de datos", "AltiData", 3000.0);

    cout << "\nAna postula a oferta 1: " << postulaciones.postular(ana, oferta1) << "\n";
    cout << "Luis postula a oferta 1: " << postulaciones.postular(luis, oferta1) << "\n";
    cout << "Luis postula a oferta 2: " << postulaciones.postular(luis, oferta2) << "\n";
    cout << "Ana repite postulacion a oferta 1: " << postulaciones.postular(ana, oferta1) << "\n";

    ofertas.cerrar(oferta2);
    cout << "Ana postula a oferta 2 (cerrada): " << postulaciones.postular(ana, oferta2) << "\n";

    reportes.generar();
    return 0;
}
