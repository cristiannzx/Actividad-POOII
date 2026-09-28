#include <iostream>
#include <string>
#include <vector>
using namespace std;
class PortalEmpleo {
private:
    struct Usuario { int id; string nombre; string correo; };
    struct Oferta { int id; string titulo; string empresa; double salario; bool activa; };
    struct Postulacion { int idUsuario; int idOferta; };

    vector<Usuario> usuarios;
    vector<Oferta> ofertas;
    vector<Postulacion> postulaciones;
    int siguienteIdUsuario;
    int siguienteIdOferta;

    bool correoValido(const string& correo) const;
    void enviarCorreo(const string& destino, const string& mensaje) const;
public:
    PortalEmpleo();
    int registrarUsuario(const string& nombre, const string& correo);
    int publicarOferta(const string& titulo, const string& empresa, double salario);
    bool postular(int idUsuario, int idOferta);
    void cerrarOferta(int idOferta);
    void generarReporte() const;
};
PortalEmpleo::PortalEmpleo() : siguienteIdUsuario(1), siguienteIdOferta(1) {}
bool PortalEmpleo::correoValido(const string& correo) const {
    size_t arroba = correo.find('@');
    return arroba != string::npos && arroba > 0 && correo.find('.', arroba) != string::npos;
}
void PortalEmpleo::enviarCorreo(const string& destino, const string& mensaje) const {
    cout << "[CORREO a " << destino << "] " << mensaje << "\n";
}
int PortalEmpleo::registrarUsuario(const string& nombre, const string& correo) {
    if (nombre.empty() || !correoValido(correo)) return -1;
    for (const auto& u : usuarios) {
        if (u.correo == correo) return -1;
    }
    usuarios.push_back({siguienteIdUsuario, nombre, correo});
    enviarCorreo(correo, "Bienvenido al portal, " + nombre);
    return siguienteIdUsuario++;
}
int PortalEmpleo::publicarOferta(const string& titulo, const string& empresa, double salario) {
    if (titulo.empty() || empresa.empty() || salario <= 0) return -1;
    ofertas.push_back({siguienteIdOferta, titulo, empresa, salario, true});
    return siguienteIdOferta++;
}
bool PortalEmpleo::postular(int idUsuario, int idOferta) {
    const Usuario* usuario = nullptr;
    for (const auto& u : usuarios) {
        if (u.id == idUsuario) usuario = &u;
    }
    const Oferta* oferta = nullptr;
    for (const auto& o : ofertas) {
        if (o.id == idOferta) oferta = &o;
    }
    if (!usuario || !oferta || !oferta->activa) return false;
    for (const auto& p : postulaciones) {
        if (p.idUsuario == idUsuario && p.idOferta == idOferta) return false;
    }
    postulaciones.push_back({idUsuario, idOferta});
    enviarCorreo(usuario->correo, "Tu postulacion a '" + oferta->titulo + "' fue registrada");
    return true;
}
void PortalEmpleo::cerrarOferta(int idOferta) {
    for (auto& o : ofertas) {
        if (o.id == idOferta) o.activa = false;
    }
}
void PortalEmpleo::generarReporte() const {
    cout << "\n===== REPORTE DEL PORTAL =====\n";
    cout << "Usuarios: " << usuarios.size() << " | Ofertas: " << ofertas.size()
              << " | Postulaciones: " << postulaciones.size() << "\n";
    for (const auto& o : ofertas) {
        cout << "- " << o.titulo << " (" << o.empresa << ", S/ " << o.salario << ", "
                  << (o.activa ? "activa" : "cerrada") << ")\n";
        for (const auto& p : postulaciones) {
            if (p.idOferta != o.id) continue;
            for (const auto& u : usuarios) {
                if (u.id == p.idUsuario) cout << "    * " << u.nombre << "\n";
            }
        }
    }
}
int main() {
    PortalEmpleo portal;
    int ana = portal.registrarUsuario("Ana Torres", "ana@correo.com");
    int luis = portal.registrarUsuario("Luis Quispe", "luis@correo.com");
    int invalido = portal.registrarUsuario("Sin Correo", "correo-malo");
    cout << "Registro con correo invalido devuelve: " << invalido << "\n\n";

    int oferta1 = portal.publicarOferta("Desarrollador C++", "TechPuno", 3500.0);
    int oferta2 = portal.publicarOferta("Analista de datos", "AltiData", 3000.0);

    cout << "\nAna postula a oferta 1: " << portal.postular(ana, oferta1) << "\n";
    cout << "Luis postula a oferta 1: " << portal.postular(luis, oferta1) << "\n";
    cout << "Luis postula a oferta 2: " << portal.postular(luis, oferta2) << "\n";
    cout << "Ana repite postulacion a oferta 1: " << portal.postular(ana, oferta1) << "\n";
    portal.cerrarOferta(oferta2);
    cout << "Ana postula a oferta 2 (cerrada): " << portal.postular(ana, oferta2) << "\n";

    portal.generarReporte();
    return 0;
}
