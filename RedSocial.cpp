#include "RedSocial.h"

using namespace std;


RedSocial::RedSocial(){
    _cantidad_amistades = 0;
}

const set<int> & RedSocial::usuarios() const{
    return _ids;
}
string RedSocial::obtener_alias(int id) const{
    return _usuarios.at(id);        // O(log n)
}

const set<string> & RedSocial::obtener_amigos(int id) const{
    return _amigos.at(id); 
}

int RedSocial::cantidad_amistades() const{
    return _cantidad_amistades;
}

void RedSocial::registrar_usuario(string alias, int id){
    if (_usuarios.empty()) {
        id_mas_popular = id;
    }
    _usuarios[id] = alias;      // O(log n) con n = _usuarios.size()
    _ids.insert(id);            // O(log n)
    set<string> _amigos_alias;
    _amigos[id] = _amigos_alias;   // O(log n)
}

void RedSocial::eliminar_usuario(int id){
    set<string> amigos_del_eliminado = _amigos.find(id) -> second;
    for (string alias_amigo : amigos_del_eliminado){
        int id_amigo = obtener_id(alias_amigo);
        desamigar_usuarios(id, id_amigo);
    }
    _ids.erase(id);        
    auto it = this -> _usuarios.find(id);
    this -> _usuarios.erase(it);
    //this->"map".find(clave) es el iterador a ese elemento 
    //(se puede hacer first/second)

    //this->"map".at(clave) es el valor asociado a esa clave 
    //(un string por ej)
}

void RedSocial::amigar_usuarios(int id_A, int id_B){
    _amigos[id_A].insert(obtener_alias(id_B));
    _amigos[id_B].insert(obtener_alias(id_A));
    _cantidad_amistades=_cantidad_amistades+1;

    if (id_A != id_mas_popular && id_B != id_mas_popular){
        if (_amigos[id_A].size() > _amigos[id_mas_popular].size()){ // A es mas popular
            id_mas_popular= id_A;
        } 
        else if (_amigos[id_B].size() > _amigos[id_mas_popular].size()){ // B es mas popular
            id_mas_popular= id_B;
        }
    }
    _amigos_del_mas_popular = _amigos[id_mas_popular];

}

void RedSocial::desamigar_usuarios(int id_A, int id_B){
    _amigos[id_A].erase(obtener_alias(id_B));
    _amigos[id_B].erase(obtener_alias(id_A));
    _cantidad_amistades=_cantidad_amistades-1;
    if (id_A == id_mas_popular || id_B == id_mas_popular){
        auto it = _amigos.begin();
        while(it != _amigos.end()){
            if (it->second.size() > obtener_amigos(id_mas_popular).size()){
                id_mas_popular = it->first;
            }
            it++;
        }
    }
    _amigos_del_mas_popular = obtener_amigos(id_mas_popular);
}

int RedSocial::obtener_id(string alias) const{
    auto it = _usuarios.begin();
    while(it != _usuarios.end()){
        if(obtener_alias(it->first) == alias){
            return it->first;
        }
        ++it;
    }
}

const set<string> & RedSocial::amigos_del_usuario_mas_popular() const{
    return _amigos_del_mas_popular;
}