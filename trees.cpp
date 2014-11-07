#include "Arbol.h"
//---------------------------------------------------------------//
Arbol::~Arbol() //destructor del arbol
{
	podar(raiz);
	raiz = NULL;
}
//---------------------------------------------------------------//
void Arbol::podar(nodoArbol *nodo) //metodo podar
{
    if (nodo) // si el nodo existe
    {
		podar(nodo->izquierda); //podamos por la izquierda
		podar(nodo->derecha); //podamos por la derecha
		delete nodo;	//borramos el nodo
		nodo = NULL;	//lo asignamos como NULL
    }
}
//---------------------------------------------------------------//
void Arbol::insertarNodo(string palindromo, bool esPalindromo) //insertar el nodo
{   
    nodoArbol *aux = raiz; 	//nodo auxiliar
    nodoArbol *nodo = new nodoArbol(palindromo, esPalindromo); //creamos el nodo del arbol
    bool nodoEncontrado = false; //auxiliar booleana

    
    while ((aux) && (palindromo != aux->palindromo) && (!nodoEncontrado)) //bucle que encuentra la posicion del nuevo nodo
    {
        if (palindromo > aux->palindromo) //si el palindromo es mayor, se va por la derecha
        {
            if (aux->derecha != NULL) aux = aux->derecha;
            else nodoEncontrado = true;
        }
        else if (palindromo < aux->palindromo) // si el palindromo es menor, se va por la izquierda
        {
            if (aux->izquierda != NULL)
                aux = aux->izquierda;
            else
                nodoEncontrado = true;
        }
    }

    if (aux == NULL) // si el auxiliar es nulo, el arbol esta vacio 
    {
        raiz = nodo;
    }
	else if (palindromo > aux->palindromo) // si es mayor, lo introducimos por la derecha
	{
		if (aux->derecha == NULL) // si la derecha es nulo 
		{
			nodo->padre = aux;
			aux->derecha = nodo;
		}
		else // si la derecha no es nula
        {
        		//intercambiamos la informacion
			nodo->derecha = aux->derecha;
			aux->derecha->padre = nodo;
			nodo->padre = aux;
			aux->derecha = nodo;
		}
	}
	else // si es menor o igual
	{
		if (aux->izquierda == NULL) // si la izquiera es NULL
		{
			nodo->padre = aux;
			aux->izquierda = nodo;
		}
		else // si la izquierda no es NULL
		{
				//se intercambia la informacion
			nodo->izquierda = aux->izquierda;
			aux->izquierda->padre = nodo;
			nodo->padre = aux;
			aux->izquierda = nodo;
		}
	}

}//fin de insertar nodo
//---------------------------------------------------------------//
bool Arbol::esHoja(nodoArbol *nodo) //determina si un arbol es hoja
{
    bool esHoja = false;

    if (nodo) // si hay un nodo 
    {
        if ((nodo->derecha == NULL) && (nodo->izquierda == NULL)) // y la izquierda y derecha son nulos
        {
            esHoja = true; // es hoja
        }
    }

    return esHoja;
} // fin de esHoja
//---------------------------------------------------------------//
void Arbol::enOrden(nodoArbol *nodo) // Muestra los palindromos en orden
{
    if(nodo) // si hay nodo
    { 
        enOrden(nodo->izquierda); //  Muestra en inorden los palindromos de la izquierda

		if(nodo->esPalindromo) // si es palindromo
		{
			cout<< "\t# " << nodo->palindromo << "\n";
		}

        enOrden(nodo->derecha); // Muestra en inorden los palindromos de la izquierda
    }
} // fin de enOrden
//---------------------------------------------------------------//
nodoArbol* Arbol::getRaiz()
{
	return raiz;
}
//---------------------------------------------------------------//
void Arbol::borrarNoPalindromos(nodoArbol *nodo) // Borra los no palindromos
{
	if(nodo)
    {

        borrarNoPalindromos(nodo->izquierda); // Borra los no palindromos de la izquierda

        borrarNoPalindromos(nodo->derecha);  // Borra los no palindromos de la derecha

		if(!nodo->esPalindromo) // Si no es palindromo
		{
			cout << "\t # Borrando: " << "\"" << nodo->palindromo << "\" \n";
    		borrar(nodo->palindromo, nodo); // se borra
		}
    }
}//fin de borrarNoPalindromos
//-------------------------------------------------------------//
nodoArbol* Arbol::maximo(nodoArbol *p) // Saca el maximo de un arbol
{
	if(p) 
	{
		if(!p->derecha) // Si no hay nodo derecha 
			return p; // Devuelve nodo 
		else
			return maximo(p->derecha); // Busca el maximo por la derecha
	}
	else
	{
		return NULL; //Devuelve NULL
	}
}//fin de maximo
//------------------------------------------------------//
void Arbol::borrar(string palindromo, nodoArbol *p) // Borra un nodo 
{
	nodoArbol * aux; //nodo auxiliar 

		if(p) // si hay nodo
		{
			if(palindromo < p->palindromo) // si el palindromo es menor
			{
				borrar(palindromo, p->izquierda); //se busca por la izquierda
			}
			else if(palindromo > p->palindromo) // Si el palindromo es mayor
			{
				borrar(palindromo, p->derecha); // se busca por la derecha
			}
			else // si el palindromo es igual
			{
				if(p->izquierda) // si hay nodos por la izquierda
				{
					if(p->derecha) // si hay nodos por la derecha
					{
						aux = maximo(p->izquierda); 			// se busca el maximo por la izquierda
						borrar(aux->palindromo, p->izquierda);	// se elimina
						p->palindromo = aux->palindromo;		// y se sustituye por el nodo
						p->esPalindromo = aux->esPalindromo;	//
					}
					else // si no hay por la derecha
					{
							// se intercambia la informacion
						p->esPalindromo = p->izquierda->esPalindromo;
						p->palindromo = p->izquierda->palindromo;
						p->derecha = p->izquierda->derecha;
						p->izquierda = p->izquierda->izquierda;
					}
				}
				else // si no hay nodo por la izquierda
				{
					if(p->derecha) //si hay nodos por la derecha
					{
							//se intercambia la informacion
						p->esPalindromo = p->derecha->esPalindromo;
						p->palindromo = p->derecha->palindromo;
						p->izquierda = p->derecha->izquierda;
						p->derecha = p->derecha->derecha;
					}
					else // si no hay nodos por la derecha
					{
						if(p == raiz) // si el nodo es igual a la raiz
						{
							delete raiz; // se borra la raiz
							raiz = NULL; // y se asigna como null
						}
						else // si no es igual a la raiz
						{
							if(p->padre->derecha == p)			//si es el hijo derecho
								p->padre->derecha = NULL;		//asignamos al de la derecha del padre como NULL
							else if((p->padre->izquierda == p))	//si el hijo es el izquierdo
								p->padre->izquierda = NULL;		//asignamos al de la izquierda como NULL

							delete p; // liberamos memoria 
							p = NULL; // asignamos como NULL
						}
					}
				}
			}
		}
}//fin de borrar
//---------------------------------------------------------------//
void Arbol::quitaCopias(nodoArbol *nodo) //quita todos las copias del arbol
{
	if(nodo) // si hay nodo
	{
		if(!esta(nodo->palindromo,nodo->izquierda)) // si el nodo n esta por la izquierda
		{
			if(nodo->izquierda) // si hay nodo izquierda
				quitaCopias(nodo->izquierda);  // se borran las copias por la izquierda

			if(nodo->derecha) // si hay nodo derecha
				quitaCopias(nodo->derecha); //se borran las copias por la derecha
		}
		else //si esta 
		{
			borrar(nodo->palindromo,nodo); // se borra el palindromo
			quitaCopias(nodo); // y se quitan copias
		}
	}
}// fin de quitaCopias
//----------------------------------------------------------------//
bool Arbol::esta(string palindromo, nodoArbol *nodo) // metodo para saber si esta un palindromo en el arbol
{
	if(nodo) // si hay nodo
	{
		if(palindromo == nodo->palindromo) // si el palindromo es igual al palindromo del nodo
		{
			return true; // se devuelve true
		}
		else if(palindromo > nodo->palindromo) // si es mayor
		{
			return esta(palindromo, nodo->derecha); // se busca por la derecha
		}
		else // si es menor o igual
		{
			return esta(palindromo, nodo->izquierda); // se busca por la izquierda
		}
	}
	else // si no hay nodo
	{
		return false; // devuelve false
	}
} // fin de esta
//----------------------------------------------------------------------//
void Arbol::mostrarRepetidas(nodoArbol *aux) //muestra los repetidos
{
	if (aux) // si hay nodo aux
	{
		//se recorre inorden 
		if (aux->izquierda) mostrarRepetidas(aux->izquierda); // se muetran los palindromos por la izquierda
		int repeticiones = numeroVeces(aux->palindromo, raiz); // se sacan las repeticiones 
		if ( repeticiones >= 2 ) // si son mayor que dos
		{
			if(aux->esPalindromo) // si es palindromo
			{
				cout << "\t#  Palindromo - " << aux->palindromo << "\n";
			}
			else // si no es palindromo
			{
				cout << "\t#  No palindromo - " << aux->palindromo << "\n";
			}
		}
		if(aux->derecha) mostrarRepetidas(aux->derecha); // se muestran los palindromos por la derecha
	}
} // fin mostrar repetidos
//---------------------------------------------------------------------//
int Arbol::numeroVeces(string palindromo, nodoArbol *posicion) // numero de veces que aparece un palindromo
{
	int contador = 0;

	if (posicion) // si hay posicion
	{
		if (posicion->izquierda) contador += numeroVeces(palindromo, posicion->izquierda); // si hay izquierdo se cuenta por la izquierda
		if (posicion->palindromo == palindromo ) contador ++; // si la palabra coincide con la que esta buscando se incrementa el contador 
		if (posicion->derecha) contador += numeroVeces(palindromo, posicion->derecha); // si hay derecha se cuenta por la derecha
	}

	return contador;
}

