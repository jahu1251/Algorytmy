#include <iostream>
using namespace std;
#include "listy.cpp"

//zamiana pierwszego i ostatniego elementu listy
void zadanie_1(node* &H){
    if(H && H->next){
        node* p1 = H;
        node* p2 = H;
        while(p1->next->next != nullptr){
            p1 = p1->next;
        }
        H = p1->next;
        H->next = p2->next;
        p1->next = p2;
        p2->next = nullptr;

    }
    else{
        cout << "Za malo elementow" << endl;
    }
}

//zamiana elementu o wartości x ze swoim następnikiem
void zadanie_2(node* &H, int x){
    if(H){
        node* p1 = H;
        Add(H, 0);
        while(p1->next != nullptr){
            if(p1->next->val == x && p1->next->next != nullptr){
                node* p2 = p1->next;
                p1->next = p2->next;
                p2->next = p2->next->next;
                p1->next->next = p2;
                p1 = p1->next->next;
            }
            else{
                p1 = p1->next;
            }
        }
        Del(H);
    }
}

//zamiana co 2 elementu miejscami
void zadanie_3(node*& H) {//done
    if (H && H->next) {
        node* p1 = H;
        node* p2 = H->next;
        H = p1->next;
        p1->next = p2->next;
        p2->next = p1;
        p2 = p1->next;
        while(p2 != nullptr) {
            if (p2->next != nullptr) {
                p1->next = p2->next;
                p2->next = p1->next->next;
                p1->next->next = p2;
                p1 = p1->next->next;
                p2 = p2->next;
            }
            else
                break;
       
        }
    }
}

//usuwanie co 2 elementu w liście
void zadanie_4(node* &H){
    if(H && H->next){
        node* p = H;
        node* p1;
        while(p && p->next){
            p1 = p->next;
            p->next = p1->next;
            delete p1;
            p = p->next;
        }
    }
}

//usuwanie elementów parzystych co do wartości
void zadanie_5(node* &H){
    if(H){
        Add(H, 0);
        node* p1 = H;
        while(p1->next != nullptr){
            if(p1->next->val % 2 == 0){
                node* p2 = p1->next;
                p1->next = p2->next;
                delete p2;
            }
            else{
                p1 = p1->next;
            }
        }
        Del(H);
    }
}

//przesuwanie parzystych elementów na koniec listy
void zadanie_6(node* &H) {
	if (H && H->next) {
		node* H1 = NULL;
		node* E1 = NULL;
		node* p;
		while (H && H->val % 2 == 0) {
			p = H;
			H = H->next;
			AddEnd(H1, E1, p);
		}
		p = H;
		node* p1;
		while (p != NULL && p->next != NULL) {
			if (p->next->val % 2 == 0) {
				p1 = p->next;
				p->next = p1->next;
				AddEnd(H1, E1, p1);
			}
				else{
				p = p -> next;
				}
        }
			if(p == nullptr){
				H = H1;
			}
			else {
				p->next = H1;
			}
	}
}

//usuwanie wszystkich elementów o podanej wartości
void zadanie_7(node* &H, int x){
    if(H){
        Add(H,0);
        node* p1 = H;
        while(p1->next != nullptr){
            if(p1->next->val == x){
                node*p2 = p1->next;
                p1->next = p2->next;
                delete p2;
            }
            else{
                p1 = p1->next;
            }
        }
        Del(H);
    }
}

//Kopia listy
void zadanie_8(node* &H){
    if(H){
        node* p1 = H;
        while(p1 != nullptr){
            for(int i = 0; i < p1->val - 1; ++i){
                Add(p1->next, p1->val);
                p1 = p1->next;
            }
            p1 = p1->next;
        }
    }
}

//odwrócenie listy
void zadanie_9(node* &H){
    if(H){
        node* p1 = H;
        while(p1->next != nullptr){
            node* p2 = p1->next;
            p1->next = p2->next;
            p2->next = H;
            H = p2;
        }
    }
}

//inna kopia listy
void zadanie_10(node *&H) {
    if (H) {
        node* e = H;
        while (e -> next != nullptr) {
            e = e->next;
        }
        node* p = H;
        while (p != nullptr) {
            Add(H, p->val);
            Add(e->next, p->val);
            p = p->next;
            if (p == e->next)
                p = nullptr;
        }
    } 
}

//usuwanie z listy elementów, które sa powyżej średniej
void zadanie_11(node* &H){
    if(H){
        node* p1 = H;
        double srednia = p1->val;;
        int i = 1;
        while(p1->next != nullptr){
            srednia += p1->next->val;
            p1 = p1->next;
            ++i;
        }
        srednia = srednia/i;
        Add(H,0);
        p1 = H;
        while(p1->next != nullptr){
            if(p1->next->val > srednia){
                node* p2 = p1->next;
                p1->next = p2->next;
                delete p2;
            }
            else{
                p1 = p1->next;
            }
        }
    }
}

//usuwanie z listy największego elementu
void zadanie_12(node* &H){
    if(H){
        node* p = H;
        int max = p->val;
        while(p->next != nullptr){
            if(p->next->val > max){
                max = p->next->val;
                p = p->next;
            }
            else{
                p = p->next;
            }
        }
        Del_x(H, max);
    }
}

void zadanie_12_v2(node* &H) {
    if (H && H->next) {
        node* p1 = H, * p2 = nullptr, * p3 = nullptr;
        int max = p1->val;
        while (p1->next != nullptr) {
            if (p1->next->val > p1->val) {
                max = p1->next->val;
                p2 = p1;
                p3 = p1->next;
            }
            p1 = p1->next;
        }
        p2->next = p3->next;
        delete p3;
    }
}

//elementy pomiędzy x i y na koniec listy
void zadanie_13(node* &H,int x, int y) {
    if (H) {
        node* p = H, * p2 = H, * p3 = H;
        while (p->val != x) {
            if (p->val == y) {
                std::cout << "Y is before X, can not realize the function\n";
                return;
            }
            else{
                p = p->next;
            }
        }
        p2 = p->next;
        while (p2->val != y){
            p2 = p2->next;
        }
        p3 = p2;
        while (p3->next != nullptr){
            p3 = p3->next;
        }
        node* p4 = p->next;
        p->next = p2;
        p3->next = p4;
        while (p4->next != p2){
            p4 = p4->next;
        }
        p4->next = nullptr;
    }
}

void zadanie_14(node* &H,int x, int y) {
        if (H) {
        node* p = H, * p2 = H, * p3 = H;
        int i = 0;
        while (p->val != x) {
            if (p->val == y) {
                std::cout << "Y is before X, can not realize the function\n";
                return;
            }
            else{
                p = p->next;
            }
        }
        p2 = p->next;
        while (p2->val != y){
            i++;
            p2 = p2->next;
        }
        p3 = p2;
        while (p3->next != nullptr){
            p3 = p3->next;
        }
        node* p4 = p->next;
        for(int j = 0;j < i; j++){
            
        }
        p->next = p2;
        p3->next = p4;
        while (p4->next != p2){
            p4 = p4->next;
        }
        p4->next = nullptr;
    }
}

int main(){

    //node* H = NULL;
    //node* H1 = NULL;
    //node* H2 = NULL;


	//Add(H, 12);
	//Add(H, 6);
	//Add(H, 2);
	//Add(H, 5);
	//Add(H, 7);
    //Add(H, 9);
    //Add(H, 12);
    //Add(H, 1);
    //Add(H, 4);
    //Add(H, 9);
 
    //Show(H);
    //zadanie_1(H);
    //zadanie_2(H,5);
    //zadanie_3(H);
    //zadanie_4(H);
    //zadanie_5(H);
    //zadanie_6(H);
    //zadanie_7(H, 12);
    //zadanie_8(H);
    //zadanie_9(H);
    //zadanie_10(H);
    //zadanie_11(H);
    //zadanie_12_v2(H);
    //zadanie_13(H,1,6);
    //zadanie_14(H,1,6);
    //Show(H);

    //int * array = getRandom();
    //int * array2 = array;
    //quickSortH(array,1,100);
    //clock_t start = clock();

    //mergeSort(array, 100);
    //cout << "Czas dzialania mergeSort wynosi " << clock() << endl;
    //mergeSort_H(array2, 100);
    //cout << "Czas dzialania mergeSort wynosi " << clock() << endl;

    /*for (int i = 0; i < 100; ++i) {
      cout << array[i] << endl;
   }
   */


    return 0;
}