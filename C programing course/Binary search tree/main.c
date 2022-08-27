#include "tree.h"
#include <stdio.h>


int main()
{
    bool flag=false;
    Ptree root=NULL;
    int size=0;
    int n;
    float key;
    float toSearch;
    int xMin;
    int i=0;
    printf("1- insert a key to your tree.\n");
    printf("2- Print the tree keys.\n");
    printf("3- Calculate the tree height.\n");
    printf("4- Find the minimum in the tree.\n");
    printf("5- search for a key in the tree.\n");
    printf("6- Print a number of the highest keys in the tree.\n");
    printf("7- to quit the program.\n");
    do
    {
        printf("Your choice: ");
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                printf("Enter a key to insert: ");
                scanf("%f", &key);
                insert(key, &root, &size);
                if(root==NULL)
                    printf("Something went wrong.\n");
                else
                    printf("The key inserted successfuly.\n");
                break;
            case 2:
                if (size==0)
                {
                    printf("The tree is empty.\n");
                    break;
                }
                printf("The tree keys are: ");
                printPreorder(root);
                printf("\n");
                break;
            case 3:
                if (size==0)
                {
                    printf("The tree is empty.\n");
                    break;
                }
                printf("The tree hieght is: %d\n", height(root));
                break;
            case 4:
                if (size==0)
                {
                    printf("The tree is empty.\n");
                    break;
                }
                printf("The minimum key is: ");
                minKey(root);
                printf("\n");
                break;
            case 5:
                if (size==0)
                {
                    printf("The tree is empty.\n");
                    break;
                }
                printf("Enter a key you wish to find: ");
                scanf("%f", &toSearch);
                searchKey(root, toSearch, &flag);
                if(flag==true)
                    printf("Found\n");
                else
                    printf("Not available.\n");
                break;
            case 6:
                if (size==0)
                {
                    printf("The tree is empty.\n");
                    break;
                }
                printf("Enter the number of keys to print: ");
                scanf("%d", &xMin);
                for(int j=1; j<=xMin; j++)
                {
                    printKmax(root, j, size, &i);
                    i=0;
                }
                printf("\n");
                break;
            case 7:
                break;
            default:
                printf("Out of options.\n");
                break;
        }
    } while (n!=7);
    emptyTree(&root);
    return 0;
}