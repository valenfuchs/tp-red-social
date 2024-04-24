#ifndef __REDSOCIAL_H__
#define __REDSOCIAL_H__

#include <string>
#include <set>
#include <iterator>
#include <map>
// TP
class RedSocial{
  public:
    RedSocial();

    const std::set<int> & usuarios() const; // O(1)
    std::string obtener_alias(int id) const; // O(log n)
    const std::set<std::string> & obtener_amigos(int id) const; // O(log n)
    int cantidad_amistades() const; // O(1)

    void registrar_usuario(std::string alias, int id); // O(log n)
    void eliminar_usuario(int id); // sin requerimiento
    void amigar_usuarios(int id_A, int id_B); // sin requerimiento
    void desamigar_usuarios(int id_A, int id_B); // sin requerimiento
    
    int obtener_id(std::string alias) const; // sin requerimiento
    const std::set<std::string> & amigos_del_usuario_mas_popular() const; // O(1)

  private:
    std::map<int, std::string> _usuarios;
    std::set<int> _ids;
    std::map<int, std::set<std::string>> _amigos;
    int _cantidad_amistades;
    int id_mas_popular;
    std::set<std::string> _amigos_del_mas_popular;
    
};

#endif

/*
REP
1) _usuarios, _ids, _amigos tienen la misma longitud (cantidad de usuarios en la red)
2) id_mas_popular es la clave en el map _amigos que tiene como valor asociado el set más largo
3) _amigos_del_mas_popular es el conjunto de los alias de los amigos del usuario más popular
4) _cantidad_amistades es la cantidad total de relaciones de amistad actualmente en la red
5) las claves de los diccionarios _usuarios y _amigos son las mismas, y son las mismas que los elem de _ids
*/