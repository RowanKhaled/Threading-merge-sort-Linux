#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>

#define MAX 100

int array[MAX];
int arr_size;
int mid;

struct index
{
    int left;
    int right;

};


void merge(int array[], int left, int mid, int right)
{
    int i, j, k;
    int counter1 = mid- left + 1;
    int counter2 =  right - mid;

    int arrayLeft[counter1]; //temp array for left part
    int arrayRight[counter2]; //temp array for right part


    for (i = 0; i < counter1; i++)  //assign values to temp array left part
        arrayLeft[i] = array[left+ i];
    for (j = 0; j < counter2; j++)  //assign values to temp array right part
        arrayRight[j] = array[mid + 1+ j];

    i = 0;
    j = 0;
    k = left;

    //sorting elements
    while (i < counter1 && j < counter2)
    {
        if (arrayLeft[i] <= arrayRight[j])
            array[k] = arrayLeft[i++];

        else
            array[k] = arrayRight[j++];

        k++;
    }

    while (i < counter1)
        array[k++] = arrayLeft[i++];

    while (j < counter2)
        array[k++] = arrayRight[j++];

}



void *mergeSort(void *parameter)


{
    pthread_t thread1,thread2;



    struct index* pr = (struct index*) parameter;
    int left = pr->left,  right= pr->right;


    if (left< right)
    {
        struct index pr1,pr2;
        int mid = (left+right)/2;

        pr1.left = left;
        pr1.right = mid;


        pr2.left = mid+1;
        pr2.right = right;


        pthread_create(&thread1,NULL,mergeSort,(void*) &pr1);

        pthread_create(&thread2,NULL,mergeSort,(void*) &pr2);


        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);

        merge(array, left, mid, right);
    }

}




int main()
{
    pthread_t tid;


    FILE *fp;
    fp= fopen("merge.txt","r");

    if(fp==NULL)
        exit(1);

    else
    {
        fscanf(fp,"%d", &arr_size);
        printf("array size is %d\n",arr_size);
        int i;
        for(i=0; i<arr_size; i++)
        {
            fscanf(fp,"%d", &array[i]);
            printf("array of %d is %d\n",i,array[i]);

        }
    }

    printf("Given array is \n");

    int i;

    for (i=0; i < arr_size; i++)
        printf("%d ", array[i]);





    struct index pr3;



    pr3.left = 0;
    pr3.right = arr_size-1;

    pthread_create(&tid,NULL,mergeSort,(void*) &pr3);

    pthread_join(tid,NULL);



    printf("\nSorted array is \n");


    for (i=0; i < arr_size; i++)
        printf("%d ", array[i]);



    return 0;
}
