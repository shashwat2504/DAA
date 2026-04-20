#include<iostream>
using namespace std;

class Mobile
{
public:
    long long mobileNo;
    string name;
    float bill;

    void input()
    {
        cout<<"Enter Mobile No: ";
        cin>>mobileNo;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Bill: ";
        cin>>bill;
    }

    void show()
    {
        cout<<mobileNo<<"\t"<<name<<"\t"<<bill<<endl;
    }
};

Mobile m[50];
int n;

// counting
int comp = 0;
int pass = 0;

//////////////////////////////////////////////////
// SWAP
//////////////////////////////////////////////////
void swap(Mobile &a, Mobile &b)
{
    Mobile temp = a;
    a = b;
    b = temp;
}

//////////////////////////////////////////////////
// QUICK SORT (Descending Mobile No)
//////////////////////////////////////////////////
int partition(int low, int high)
{
    long long pivot = m[high].mobileNo;
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        comp++;
        if(m[j].mobileNo > pivot)
        {
            i++;
            swap(m[i], m[j]);
        }
    }

    swap(m[i+1], m[high]);
    return i+1;
}

void quickSort(int low, int high)
{
    if(low < high)
    {
        pass++;
        int pi = partition(low, high);

        quickSort(low, pi-1);
        quickSort(pi+1, high);
    }
}

//////////////////////////////////////////////////
// HEAP SORT (Ascending Bill)
//////////////////////////////////////////////////
void heapify(int size, int i)
{
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < size)
    {
        comp++;
        if(m[left].bill < m[smallest].bill)
            smallest = left;
    }

    if(right < size)
    {
        comp++;
        if(m[right].bill < m[smallest].bill)
            smallest = right;
    }

    if(smallest != i)
    {
        swap(m[i], m[smallest]);
        heapify(size, smallest);
    }
}

void heapSort()
{
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(n, i);

    for(int i = n-1; i >= 0; i--)
    {
        pass++;
        swap(m[0], m[i]);
        heapify(i, 0);
    }
}

//////////////////////////////////////////////////
// MERGE SORT (Ascending Mobile No)
//////////////////////////////////////////////////
void merge(int low, int mid, int high)
{
    Mobile temp[50];

    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high)
    {
        comp++;
        if(m[i].mobileNo < m[j].mobileNo)
        {
            temp[k] = m[i];
            i++;
        }
        else
        {
            temp[k] = m[j];
            j++;
        }
        k++;
    }

    while(i <= mid)
    {
        temp[k++] = m[i++];
    }

    while(j <= high)
    {
        temp[k++] = m[j++];
    }

    for(int x = low; x <= high; x++)
        m[x] = temp[x];
}

void mergeSort(int low, int high)
{
    if(low < high)
    {
        pass++;
        int mid = (low + high) / 2;

        mergeSort(low, mid);
        mergeSort(mid+1, high);

        merge(low, mid, high);
    }
}

//////////////////////////////////////////////////
// DISPLAY
//////////////////////////////////////////////////
void display()
{
    cout<<"\nMobileNo\tName\tBill\n";
    for(int i=0;i<n;i++)
        m[i].show();
}

//////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////
int main()
{
    int ch;

    do
    {
        cout<<"\n===== MENU =====\n";
        cout<<"1. Input\n";
        cout<<"2. Quick Sort (Desc MobileNo)\n";
        cout<<"3. Heap Sort (Asc Bill)\n";
        cout<<"4. Merge Sort (Asc MobileNo)\n";
        cout<<"5. Display\n";
        cout<<"6. Exit\n";

        cout<<"Enter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
                cout<<"Enter number of users: ";
                cin>>n;
                for(int i=0;i<n;i++)
                {
                    cout<<"\nUser "<<i+1<<endl;
                    m[i].input();
                }
                break;

            case 2:
                comp = pass = 0;
                quickSort(0, n-1);
                cout<<"\nQuick Sort (Descending MobileNo)\n";
                display();
                cout<<"Passes: "<<pass<<" Comparisons: "<<comp<<endl;
                break;

            case 3:
                comp = pass = 0;
                heapSort();
                cout<<"\nHeap Sort (Ascending Bill)\n";
                display();
                cout<<"Passes: "<<pass<<" Comparisons: "<<comp<<endl;
                break;

            case 4:
                comp = pass = 0;
                mergeSort(0, n-1);
                cout<<"\nMerge Sort (Ascending MobileNo)\n";
                display();
                cout<<"Passes: "<<pass<<" Comparisons: "<<comp<<endl;
                break;

            case 5:
                display();
                break;

            case 6:
                cout<<"Exiting...\n";
                break;

            default:
                cout<<"Invalid choice\n";
        }

    }while(ch != 6);

    return 0;
}