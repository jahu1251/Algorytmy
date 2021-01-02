#include <iostream>
#include <ctime>
#include <time.h>
using namespace std;

//tworzenie węzła listy
struct node{
    int val;
    node* next;
};

//dodawanie elemtnu na początek listy
void Add(node* &H, int x){
    node* p = new node;
    p->val = x;
    p->next = H;
    H = p;
}

//liczeine elementów listy
int Count(node* H){
    int c = 0;
    node* p = H;
    while(p){
        ++c;
        p = p->next;
    }
    return c;
}

//wyświetlanie zawartości listy
void Show(node *H){
    cout << "H -> ";
    node *p = H;
    while(p != nullptr){
        cout << p -> val << " -> ";
        p = p -> next;
    }
    cout << "NULL" << std::endl;
}


//usuwanie elementu z początlu listy
void Del(node* &H){
    if(H != nullptr){
        node* p = H;
        H = H->next;
        delete p;
    }
    else{
        cout << "Lista nie istnieje" << endl;
    }
}

//usuwanie elementu o wskazanej wartości z listy
void Del_x(node* &H, int x){
       Add(H,0);
       node* p = H;
       while(p->next != nullptr && p->next->val != x){
           p = p->next;
       }
           if(p->next != nullptr){
               Del(p->next);
           }
        Del(H);
}

//zamiana miejscami dwóch pierwszych elementów listy
void Swap(node* &H){
    if(H && H->next){
        node* p = H;
        H = H->next;
        p->next = H->next;
        H->next = p;
    }
}

//zamiana miejscami dowolnych dwóch elementów listy
void Swap_2(node* &H, node* e){
    if(H && H->next){
        if(e == nullptr){
            Swap(H);
        }
        else{
            node* k = e->next;
            e->next = k->next; 
            k->next = k->next->next; 
            e->next->next = k;
        }
    }
}

//doklejanie listy na koniec innej listy
void AddEnd(node*& H, node*& E, node* p) {
	if (H == NULL) {
		H = p;
		E = p;
		H->next = NULL;
	}
	else {
		E->next = p;
		E = p;
		p->next = NULL;
	}
}

//odwracanie tablicy
void reverse(node*& H) {
    node* p1, * p2;
    if (H) {
        p2 = H;
        while (p2->next != nullptr) {
            p1 = p2->next;
            p2->next = p1->next;
            p1->next = H;
            H = p1;
        }
    }
}



//dzielenie listy na dwie osobne
void Split(node*& H, node*& H1, node*& H2) {
    if (H != nullptr && H->next != nullptr) {
        H1 = H;
        H = H->next;
        H1->next = nullptr;
        H2 = H;
        H = H->next;
        H2->next = nullptr;        
        if (H != nullptr) {
            node* p1 = H1, *p2 = H2;
            while (H != nullptr) {
                p1->next = H;
                p1 = p1->next;
                if (H->next != nullptr) {
                    H = H->next;
                    p2->next = H;
                    p2 = p2->next;
                }
                H = H->next;
            }
            p1->next = nullptr;
            p2->next = nullptr;
        }
    }
    else {
        H1 = H;
        H = H->next;
        H1->next = nullptr;
    }
}

//scalanie tablic
void Merge(node*& H1, node*& H2, node*& H) { 
    if (H1 != nullptr && H2 != nullptr) {
        if (H1->val <= H2->val) {
            H = H1;
            H1 = H1->next;
        }
        else {
            H = H2;
            H2 = H2->next;
        }
        node* p = H;
        while (H1 != nullptr && H2 != nullptr) {
            if (H1->val <= H2->val) {
                p->next = H1;
                H1 = H1->next;
                p = p->next;
            }
            else {
                p->next = H2;
                H2 = H2->next;
                p = p->next;
            }
        }
        if (H1 == nullptr) {
            p->next = H2;
            H2 = nullptr;
        }
        else if (H2 == nullptr) {
            p->next = H1;
            H1 = nullptr;
        }
    }
    else if (H1 == nullptr) {
        H = H2;
        H2 = nullptr;
    }
    else if (H2 == nullptr) {
        H = H1;
        H1 = nullptr;
    }
}

//sortowaine przez scalanie
void MergeSort(node*& H) {
    node* H1 = nullptr, * H2 = nullptr;
    if (H == nullptr || H->next == nullptr)
        return;
    Split(H, H1, H2);
    MergeSort(H1);
    MergeSort(H2);
    Merge(H1, H2, H);
}

//sortowanie bąbelkowe z usprawnieniem
void bubble_sort(node*& H) {
    if (H != nullptr && H->next != nullptr) {
        node* p = nullptr, *e1 = nullptr, * e2 = nullptr;
        bool ifswap = 1;
        while (ifswap == 1) {
            ifswap = 0;
                if (H->val > H->next->val) {
                    Swap(H);
                    ifswap = 1;
                    e2 = H->next;
                }
                p = H;
                while (p->next->next != nullptr && p->next->next != e1) {
                    if (p->next->val > p->next->next->val) {
                        Swap_2(H,p);
                        ifswap = 1;
                        e2 = p->next->next;
                    }
                    p = p->next;
                }
                e1 = e2;
        }
    }
}

//funkcje potrzebne do sortowania grzebieniowego 
node* setPrev(node*& H, int x) {
    node* p = H;
    while (x > 1) {
        p = p->next;
        --x;
    }
    return p;
}

void comb_swap(node*& H, node* prevX, node* prevY) {
    node* currX = nullptr;
    if (prevX == nullptr)
        currX = H;
    else
        currX = prevX->next;
    node* currY = prevY->next;
    
    if (prevX != nullptr)
        prevX->next = currY;
    else
        H = currY;

    prevY->next = currX;

    node* tmp = currY->next;
    currY->next = currX->next;
    currX->next = tmp;
}

//sortowanie grzebieniowe
void comb_sort(node*& H) {
    int cntr = 0;
    node* p = nullptr;
    while (p != nullptr) {
        ++cntr;
        p = p->next;
    }
    p = nullptr;
    int space = cntr / 1.3;
    while (space > 1) {
        node* p2 = setPrev(H, space);

        if (p2 != nullptr && p2->next != nullptr) {
            if (H->val > p2->next->val)
                comb_swap(H, nullptr, p2);
        }
        p2 = p2->next;
        node* p1 = H;
        while (p2 != nullptr && p2->next != nullptr) {
            if (p1->next->val > p2->next->val) 
                comb_swap(H, p1, p2);

            p1 = p1->next;
            p2 = p2->next;
        }
        --space;
    }
    bubble_sort(H);
    
}

void tab_swap_val(int a, int b)
{
	int c;
	c = b;
	b = a;
	a = c;
 
}
 
 
 
void Heapify(int n, int *tab, int heapsize){

	int l = 2 * n;
	int r = 2 * n + 1;
	int largest;
 
	if (l <= heapsize && tab[l] > tab[n]){

		largest = l;
	}
 
	else
		largest = n;
 
	if (r <= heapsize && tab[r] > tab[largest]){

		largest = r;
	}
 
	if (largest != n){

		swap(tab[n], tab[largest]);
		Heapify(largest, tab, heapsize);
	}
}
 
void Heapsort(int n, int* tab){
 
	for (int i = n / 2; n > 0; n--){

		Heapify(i,tab,n);
	}
 
 
	for(int i = n; i>1; i--){
        
		swap(tab[1], tab[i]);
		n--;
		Heapify(0, tab, n);
	}
 
}

//generowanie tablicy
int * getRandom( ) {

   static int  r[100];

   srand( (unsigned)time( NULL ) );
   
   for (int i = 0; i < 100; ++i) {
      r[i] = rand();
      cout << r[i] << endl;
   }

   return r;
}

//hybrydowe quicksort na tablicach

long partition(int *tab, long l, long p) {
  int x = tab[p];
  long i = l - 1;
  for(; l < p; ++l) {
    if(tab[l] <= x)
      swap(tab[++i], tab[l]);
  }
  swap(tab[i + 1], tab[p]);
  return i + 1;
}
 
void bubbleSort_tab(int *tab, int size) {
  bool swapp = true;
  int k = 0;
  for(int i = 0; i < size && swapp; ++i) {
    swapp = false;
    for(int j = 0; j < size-i || j < k; ++j) {
      if (tab[j] > tab[j+1]) {
        swapp = true;
        swap(tab[j], tab[j+1]);
        k = j;
      }
    }
  }
}
 
void quickSortH(int *tab, long l, long p) {
  if(p - l > 10) {
    long par = partition(tab, l, p);
    quickSortH(tab, l, par-1);
    quickSortH(tab, par+1, p);
  } else {
    bubbleSort_tab(tab+l, p-l);
  }
}

//merge sort na tablicach

void copy(int arr[], int l, int r, int arr1[]) {
    for (int i = 0; i < (r-l); i++) {
        arr1[i] = arr[l + i];
    }
}
void merge(int *arr, int *arr1, int *arr2, int g, int h){
    int i = 0; int j = 0; int k = 0;
    while(1){
        if(i < g && j < h){

            if(arr1[i] < arr2[j]){
                arr[k] = arr1[i];
                ++i;
                ++k;
            }

            else{
                arr[k] = arr2[j];
                ++j;
                ++k;
            }
        }

        else if(i == g){
            for(; j < h; ++j, ++k){
                arr[k] = arr2[j];
            }
            break;
        }

        else if(j == h){
            for(; i < g; ++i, ++k){
                arr[k] = arr1[i];
            }
            break;
        }

        else if(i == g && j == h){
            break;
        }
    }
}

void mergeSort(int *arr, int size){
    if(size < 2){
        return;
    }
    int g = size / 2; 
    int h = size - g; 
    int arr1[g]; 
    int arr2[h];
    copy(arr, 0, g, arr1);
    copy(arr, g, size, arr2);
    mergeSort(arr1, g);
    mergeSort(arr2, h);
    merge(arr, arr1, arr2, g, h);
}

void mergeSort_H(int *arr, int size){
    if(size < 2){
        return;
    }
    else if(size <= 10){
        bubbleSort_tab(arr, size);
        return;
    }
    int g = size / 2; 
    int h = size - g; 
    int arr1[g]; 
    int arr2[h];
    copy(arr, 0, g, arr1);
    copy(arr, g, size, arr2);
    mergeSort(arr1, g);
    mergeSort(arr2, h);
    merge(arr, arr1, arr2, g, h);
}

