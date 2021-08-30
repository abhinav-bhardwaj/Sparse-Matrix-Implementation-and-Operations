#include <iostream>
#include <stdio.h>
using namespace std;

#define max_row 20

class sparse {
    int r,c,t;
    int tab[max_row][3];
    public:
        sparse() {    
            tab[0][2]=0;
        }
        sparse(int ro, int co, int to) {
            r=ro;
            c=co;
            t=to;
            tab[0][2]=0;
        }
        int create_table();
        int exist();
        void display_table();
        void display_matrix();
        int insert(int,int,int);
        int remove(int,int);
        int modify(int,int,int);
        int addition(sparse);
        sparse transpose();
        int multiply(sparse);
        int ret_row() {
            return r;
        }
        int ret_col() {
            return c;
        } 
        int ret_t() {
            return t;
        }
};

int menu();

int main() {
    char ch;
    sparse matA,matB;
    int ret,n,ro,co,to;
    do {
        ch = menu();
        switch(ch) {
            case 1 :
                cout<<"\n\tCREATION\n";
                cout<<"Enter no. of row and column of Sparse Matrix : ";
                cin>>ro>>co;
                cout<<"Enter no. of rows for Sparse table (must be less than (r*c)/2): ";
                cin>>to;
                matA = sparse(ro,co,to);
                ret = matA.create_table();
                if (ret==0) {
                    matA.display_table();
                    matA.display_matrix();
                }
                break;
            case 2 :
                cout<<"\n\tDISPLAY\n"; 
                if (matA.exist()==0) {
                    matA.display_table();
                    matA.display_matrix();
                }
                else {
                    cout<<"\nSparse Table is empty\n";
                }
                break;
            case 3 : 
                cout<<"\n\tINSETION\n";
                if ((matA.ret_t()+1)>((matA.ret_row()*matA.ret_col())/2)) {
                    cout<<"ERROR! No. of non-zero elements will be greater than zero elements\n";
                }
                else {
                    cout<<"Enter row and column no. : ";
                    cin>>ro>>co;
                    cout<<"Enter non-zero value : ";
                    cin>>n;
                    ret = matA.insert(ro,co,n);
                    if (ret!=1) {
                        matA.display_table();
                        matA.display_matrix();
                    }
                    else {
                        cout<<"Max no. of row or column exceeded!";
                        getchar();
                    }
                }
                break;
            case 4 : 
                cout<<"\n\tREMOVAL\n";
                if (matA.exist()==0) {
                    cout<<"\nEnter row and column to be removed : ";
                    cin>>ro>>co;
                    ret = matA.remove(ro,co);
                    if (ret==0) {
                        cout<<"\nRemoved Sucessfully";
                        matA.display_table();
                        matA.display_matrix();
                    }
                    else {
                        cout<<"\nGiven entry could not be found in table";
                    }
                }
                else {
                    cout<<"\nSparse Table is empty";
                }
                getchar();
                break;
            case 5 : 
                cout<<"\n\tMODIFICATION\n";
                if (matA.exist()==0) {
                    cout<<"\nEnter row and column to be modified : ";
                    cin>>ro>>co;
                    cout<<"Enter the new value : ";
                    cin>>n;
                    ret = matA.modify(ro,co,n);
                    if (ret==0) {
                        cout<<"\nModified Sucessfully";
                        matA.display_table();
                        matA.display_matrix();
                    }
                    else {
                        cout<<"\nGiven entry could not be found in table";
                    }
                }
                else {
                    cout<<"\nSparse Table is empty";
                }
                getchar();
                break;
            case 6 : 
                cout<<"\n\tADDITION";
                if (matA.exist()==0) {
                    cout<<"Enter no. of rows for new Sparse table (must be less than (r*c)/2): ";
                    cin>>to;
                    matB = sparse(matA.ret_row(),matA.ret_col(),to);
                    ret = matB.create_table();
                    if (ret==0) {
                        matB.display_table();
                        matB.display_matrix();
                        ret = matA.addition(matB);
                        if (ret==0) {
                            cout<<"\nAdded successfully\n";
                        }
                        else { 
                            cout<<"\n\nIncompatible addition!\n";
                            getchar();
                        }
                    }
                }
                else {
                    cout<<"\nSparse Table is empty\n";
                }
                break;
            case 7 : 
                cout<<"\n\tTRANSPOSITION\n";
                if (matA.exist()==0) {
                    sparse matT = matA.transpose();
                    matT.display_table();
                    matT.display_matrix();
                }
                else {
                    cout<<"\nSparse Table is empty\n";
                    getchar();
                }
                break;
            case 8 : 
                cout<<"\n\tMULTIPLICATION\n";
                if (matA.exist()==0) {
                    cout<<"Enter row and column of Sparse Matrix : ";
                    cin>>ro>>co;
                    cout<<"Enter no. of rows for Sparse table (must be less than (r*c)/2): ";
                    cin>>to;
                    matB = sparse(ro,co,to);
                    ret = matB.create_table();
                    if (ret!=1) {
                        matB.display_table();
                        matB.display_matrix();
                        ret = matA.multiply(matB);
                        if (ret==0) {
                            cout<<"\nMultiplied successfully\n";
                        }
                        else {
                            cout<<"\n\nIncompatible multiplication!\n";
                            getchar();
                        }
                    }
                }
                else {
                    cout<<"\nSparse Table is empty\n";
                }
                break;
            case 9 :
                cout<<"\n\nExiting....\n"; 
                break;
            default : 
                cout<<"\n\nInvalid Choice!!";
                cout<<"\nSelect again...";
                getchar();
                break;
        }
    }while(ch!=9);
    return 0;
}

int menu() {
    int ch;
    cout<<"\n\t---MENU---";
    cout<<"\n1. Create Sparse matrix";
    cout<<"\n2. Display Sparse Matrix";
    cout<<"\n3. Insert an element to sparse matrix";
    cout<<"\n4. Delete an element from sparse matrix";
    cout<<"\n5. Modify an element of sparse matrix";
    cout<<"\n6. Add two sparse matrices";
    cout<<"\n7. Transpose sparse matrix";
    cout<<"\n8. Multiply two sparse matrices";
    cout<<"\n9. Exit";
    cout<<"\n\nSelect from above : ";
    cin>>ch;
    return ch;    
}

int sparse::create_table() {
    int a,b,n;
    if (t>((r*c)/2)) {
        cout<<"ERROR! No. of non-zero elements are greater than zero elements\n";
        return 1;
    }
    cout<<"Enter values of Table for Sparse Matrix : \n";
    for (int i=0;i<t;i++) {
        cout<<"Enter row and column no. : ";
        cin>>a>>b;
        if (r<a || c<b) {
            cout<<"Max no. of row or column exceeded!";
            t=i;
            return 2;
        }
        cout<<"Enter non-zero value : ";
        cin>>n;
        tab[i][0]=a;
        tab[i][1]=b;
        tab[i][2]=n;
    }
    return 0;
}
void sparse::display_table() {
    cout<<"\nTable\n";
    cout<<"Row\tColumn\tValue\n";
    for (int i=0;i<t;i++) {
        cout<<tab[i][0]<<"\t"<<tab[i][1]<<"\t"<<tab[i][2]<<"\n";
    }
    getchar();
    return;
}
int sparse::exist() {
    if (tab[0][2]==0) {
        return 1;
    }
    else {
        return 0;
    }
}
void sparse::display_matrix() {
    cout<<"\nSPARSE MATRIX\n";
    int k=0;
    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            if (i==tab[k][0] && j==tab[k][1]) {
                cout<<tab[k][2]<<" ";
                k++;
            }
            else {
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
    getchar();
    return;
}
int sparse::insert(int ro, int co, int n) {
    if (ro>r || co>c) {
        return 1;
    }
    tab[t][0]=ro;
    tab[t][1]=co;
    tab[t][2]=n;
    t=t+1;
    return 0;
}
int sparse::remove(int ro, int co) {
    for (int i=0;i<t;i++) {
        if (tab[i][0]==ro && tab[i][1]==co) {
            for (int j=i;j<t;j++) {
                tab[j][0] = tab[j+1][0];
                tab[j][1] = tab[j+1][1];
                tab[j][2] = tab[j+1][2];
            }
            t=t-1;
            return 0;
        }
    }
    return 1;
}
int sparse::modify(int ro, int co, int n) {
    for (int i=0;i<t;i++) {
        if (tab[i][0]==ro && tab[i][1]==co) {
            tab[i][2] = n;
            return 0;
        }
    }
    return 1;
}
int sparse::addition(sparse mat) {
    if (r!=mat.r || c!=mat.c) {
        return 1;
    }
    int i=0,j=0,n;
    sparse matAdd = sparse(r,c,0);
    while (i<t && j<mat.t) {
        if (tab[i][0]>mat.tab[j][0] || 
            (tab[i][0]==mat.tab[j][0] && 
            tab[i][1]>mat.tab[j][1])) {
            matAdd.insert(mat.tab[j][0],mat.tab[j][1],mat.tab[j][2]);
            j++;
        }
        else if (tab[i][0]<mat.tab[j][0] || 
            (tab[i][0]==mat.tab[j][0] && 
            tab[i][1]<mat.tab[j][1])) {
            matAdd.insert(tab[i][0],tab[i][1],tab[i][2]);
            i++;
        }
        else {
            n = tab[i][2] + mat.tab[j][2];
            matAdd.insert(tab[i][0],tab[i][1],n);
            i++;
            j++;
        }
    }
    while (i<t) {
        matAdd.insert(tab[i][0],tab[i][1],tab[i][2]);
        i++;
    }
    while (j<mat.t) {
        matAdd.insert(mat.tab[j][0],mat.tab[j][1],mat.tab[j][2]);
        j++;
    }
    matAdd.display_table();
    matAdd.display_matrix();
    return 0;
}
sparse sparse::transpose() {
    sparse matT(r,c,t);
    int k=0;
    for (int i=0;i<c;i++) {
        for (int j=0;j<t;j++) {
            if (i==tab[j][1]) {
                matT.tab[k][0] = tab[j][1];
                matT.tab[k][1] = tab[j][0];
                matT.tab[k][2] = tab[j][2];
                k++;
            }
        }
    }
    //matT.display_table();
    //matT.display_matrix();
    return matT;
}
int sparse::multiply(sparse mat) {
    if (c != mat.r) {
        return 1;
    }
    sparse matMul(r,mat.r,0);
    int i,j;
    int a,b;
    int summ;
    mat = mat.transpose();
    int tempi,tempj;
    for (i=0;i<t;) {
        a = tab[i][0];
        for (j=0;j<mat.t;) {
            b = mat.tab[j][0];
            tempi = i;
            tempj = j;
            summ = 0;
            while (tempi<t && tab[tempi][0]==a && tempj<mat.t && mat.tab[tempj][0]==b) {
                if (tab[tempi][1] < mat.tab[tempj][1])
                    tempi++;
                else if (tab[tempi][1] > mat.tab[tempj][1])
                    tempj++;
                else
                    summ+=tab[tempi++][2]*mat.tab[tempj++][2];
                    //tempi++;
                    //tempj++;
            }
            if (summ!=0)
                matMul.insert(a,b,summ);
            while (j<mat.t && mat.tab[j][0] == b)
                j++;
        } 
        while (i<t && tab[i][0]==a)
            i++;
    }
    matMul.display_table();
    matMul.display_matrix();
    return 0;
}
