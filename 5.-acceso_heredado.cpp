#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;
class Padre {
private:
    void metodoPrivadoA() const;
    void metodoPrivadoB() const;

protected:
    void metodoProtegido() const;

public:
    void metodoPublico() const;
    void ejecutarPrivadosInternamente() const;
};

template <typename T, typename = void>
struct AccedePublico : false_type {};
template <typename T>
struct AccedePublico<T, void_t<decltype(declval<const T&>().metodoPublico())>> : true_type {};

template <typename T, typename = void>
struct AccedePrivadoA : false_type {};
template <typename T>
struct AccedePrivadoA<T, void_t<decltype(declval<const T&>().metodoPrivadoA())>> : true_type {};

template <typename T, typename = void>
struct AccedePrivadoB : false_type {};
template <typename T>
struct AccedePrivadoB<T, void_t<decltype(declval<const T&>().metodoPrivadoB())>> : true_type {};

class Hija : public Padre {
public:
    void usarMetodosAccesibles() const;

    template <typename T = Hija>
    static auto probarProtegido(int) -> decltype(declval<const T&>().metodoProtegido(), true_type{});
    static false_type probarProtegido(...);

    static constexpr bool puedeAccederProtegido() {
        return decltype(probarProtegido(0))::value;
    }
};

void Padre::metodoPrivadoA() const {
    cout << "Padre::metodoPrivadoA()\n";
}

void Padre::metodoPrivadoB() const {
    cout << "Padre::metodoPrivadoB()\n";
}

void Padre::metodoProtegido() const {
    cout << "Padre::metodoProtegido()\n";
}

void Padre::metodoPublico() const {
    cout << "Padre::metodoPublico()\n";
}

void Padre::ejecutarPrivadosInternamente() const {
    metodoPrivadoA();
    metodoPrivadoB();
}

void Hija::usarMetodosAccesibles() const {
    metodoPublico();
    metodoProtegido();
}

#if defined(PRUEBA_ERROR_A)
class HijaConError : public Padre {
public:
    void intentar() const {
        metodoPrivadoA();
    }
};
#elif defined(PRUEBA_ERROR_B)
class HijaConError : public Padre {
public:
    void intentar() const {
        metodoPrivadoB();
    }
};
#endif

static const char* resultado(bool accesible) {
    return accesible ? "ACCESIBLE" : "INACCESIBLE (error de compilacion si se intenta usar)";
}

int main() {
    Hija h;

#if defined(PRUEBA_ERROR_A) || defined(PRUEBA_ERROR_B)
    HijaConError hijaConError;
    hijaConError.intentar();
#endif

    cout << "=== Pruebas de acceso a los metodos de Padre ===\n";
    cout << "metodoPublico    : " << resultado(AccedePublico<Hija>::value) << "\n";
    cout << "metodoProtegido  : " << resultado(Hija::puedeAccederProtegido()) << "\n";
    cout << "metodoPrivadoA   : " << resultado(AccedePrivadoA<Hija>::value) << "\n";
    cout << "metodoPrivadoB   : " << resultado(AccedePrivadoB<Hija>::value) << "\n";

    static_assert(AccedePublico<Hija>::value, "publico debe ser accesible");
    static_assert(Hija::puedeAccederProtegido(), "protegido debe ser accesible desde Hija");
    static_assert(!AccedePrivadoA<Hija>::value, "privado A NO debe ser accesible");
    static_assert(!AccedePrivadoB<Hija>::value, "privado B NO debe ser accesible");

    cout << "\n=== Metodos accesibles usados por la subclase ===\n";
    h.usarMetodosAccesibles();

    cout << "\n=== Los privados solo se ejecutan dentro de la clase Padre ===\n";
    h.ejecutarPrivadosInternamente();
    return 0;
}
