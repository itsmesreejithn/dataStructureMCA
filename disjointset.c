#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int *setArr = NULL,*setRep=NULL,*elements=NULL,elementsCount=0,setLength=0,setRepLength=0,
// used in recursive display fn, to display set properly
recursionCount=0;

void displayArray(){
    printf("\nEntered elements are :");
    for(int i=0;i<elementsCount;i++) printf(" %d",elements[i]);
	printf("\nArray elements are : ");
	for(int i=0;i<setLength;i++){
		printf(" %d",setArr[i]);	
	}

	printf("\nArray representative elements are : ");
	for(int i=0;i<setRepLength;i++){
		printf(" %d",setRep[i]);	
	}
    printf("\n");
}

/**
 * @brief Set the Union object
 * 
 * @param set1root - root of set 1
 * @param set2root - root of set 2 
 */
void setUnion(int set1root,int set2root){
    int no_of_elements;
    if(set1root>set2root)
    {
        no_of_elements = setArr[set2root]; //getting no_of_elements in set2
        setArr[set2root] += no_of_elements;
        setArr[set2root] = setArr[set1root]; // getting the root of set2 and setting it's value as the root of set1 
    }
    else 
    {
        no_of_elements = setArr[set1root]; //getting no_of_elements in set1
        setArr[set2root] += no_of_elements;
        setArr[set1root] = setArr[set2root]; // getting the root of set1 and setting it's value as the root of set2 
    }
}
/**
 * @brief fn for searching an element in array
 * 
 * @param element to be searched
 * @param arr pointer to set
 * @param length of set
 * @return index position of element
 */
int search(int element, int *arr, int length){
    int pos; 
    bool found = false;
    for(int i=0;i<length;i++){
        if(arr[i]==element){
            pos = i; 
            found = true; 
            break;
        }
    }
    if(found){
        return pos;
    }
    else{
        return -1;
    }
}
// fn for intializing block of array created by realloc to 0
void setInit(int eIndex){
    for(int i=0; i<eIndex; i++){
        // checking index present in elements previously entered 
        if(search(i,elements,elementsCount)==-1)
        {
            // printf("\n%d changed to 0",setArr[i]);
            setArr[i] = 0;
        }
    }
}
// fn for reading set elements
void readElements(int setNo){
    int element, loop =1,temp;
    bool setRepresentative = true;
    printf("\nEnter -1 to exit\n");
    int i = elementsCount;
    printf("\nEnter elements : \n");
    while(true){
        if(element==-1) break;
        else
        {
            scanf("%d",&element); 
            if(element != -1){
                temp = setLength;// saving current value of set
                if(search(element,elements,elementsCount)==-1)
                {
                    // saving element entry 
                    elements = realloc(elements,(++elementsCount)*sizeof(int));
                    elements[i] = element;
                    printf("\nEntered element is : %d",elements[i]);
                    i++;
                    if(setRepresentative)
                    {
                        // printf("\nSetting set rep as %d",element);
                        setRep = realloc(setRep,(++setRepLength)*sizeof(int));
                        // printf("\nset Rep length increased to %d\n",setRepLength);
                        if (element>=setLength) 
                        {
                            setLength = element+1;
                            setArr = realloc(setArr,setLength*sizeof(int));
                            setInit(setLength);
                        }
                        // printf("\nset length increased to %d\n",setLength);
                        setArr[element] = -1;
                        // printf("\nroot %d set as -1\n",element);
                        setRep[setRepLength-1] = element;
                        // printf("\nset rep is %d\n",setRep[setRepLength-1]);
                        setRepresentative = false;
                    }
                    else
                    {
                        if(element>=setLength){
                                // printf("\n%d >= %d \n",element,setLength);
                                setLength = element+1;
                                setArr = realloc(setArr,(setLength)*sizeof(int));
                                setInit(setLength);
                                // printf("\nResized array");
                            }
                            // assigning root value to element index and decrementing value at root index
                            setArr[element] = setRep[setNo];
                            // value at set[setRep[setNo]] represents no of elements in that set
                            setArr[setRep[setNo]] = setArr[setRep[setNo]] - 1;
                            // printf("\nno of elements in set is %d\n",setArr[setRep[setNo]]);
                    }
                    displayArray();
                }
                else
                {
                    printf("\nElement already entered!!\nEnter new one : ");
                }
            } 
        }
    }
}
int displaySet(int setRep){
    int temp,root = setRep;
    recursionCount = 0;
    if(search(root,setArr,setLength)==-1)
    {
        return root;
    } 
    else {
        printf("{");
        printf(" %d,",root);
        recursionCount++;
        for(int i=0;i<setLength;i++)
        {
            if(root==setArr[i])
            {
                temp = recursionCount;
                int element = displaySet(i);
                recursionCount = temp;
                printf(" %d",element);
                recursionCount++;
                // print comma when not printing last value of a set
                if (recursionCount!=-setArr[root]) printf(",");
                else recursionCount=0;// resetting value for avoiding confilts when multiple sets are displayed 
            }
        }
        printf(" }");
    }
}
void displayAllSets() {
    int setCount = 0;
    for (int i = 0; i<setLength;i++)
    {
        if(setArr[i]<0) // if set root found
        {
            int root = i;
            printf("\nSet%d  : ",setCount+1);
            displaySet(i); // pass set representative
            setCount++;
        }
    }
}
void weightedUnion(int set1Rep,int set2Rep){
    int weight = setArr[set1Rep] + setArr[set2Rep];
    // comparing weights
    if(-setArr[set1Rep] > -setArr[set2Rep]){
        setArr[set1Rep] = weight;
        setArr[set2Rep] = set1Rep;// setting second sets root as first sets root
    }
    else{
        setArr[set2Rep] = weight;
        setArr[set1Rep] = set2Rep;// setting first sets root as second sets root
    }
    setInit(setLength);
}

int collapsingFind(int i){
    int s=0,r=i;
    while(setArr[r]>0) r=setArr[r];
    while(i!=r){
        s = setArr[i];
        setArr[i] = r;
        i=s;
    }
    return r;
}
void main(){
    system("clear");
	int choice =1;
	while(choice!=0)
	{
		printf("\n1 - Enter set");
		printf("\n2 - Display Array");
		printf("\n3 - Display particular set");
		printf("\n4 - Display all sets");
		printf("\n5 - Perform Weighted Union");
		printf("\n6 - Perform Collapsing Find");
		printf("\n0 - Exit");
		printf("\nEnter your choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
                {
                    readElements(setRepLength); // passing set number
                    break;	
				}
			case 2:
                {
                    displayArray();
                    break;	
				}
            case 3:
                {
                    int setRep;
                    printf("\nEnter representative of set : ");
                    scanf("%d",&setRep);
                    displaySet(setRep);
                    break;
                }
            case 4:
                {
                    displayAllSets();
                    break;
                }
            case 5:
                {
                    int set1Rep,set2Rep;
                    printf("\nEnter representative of first set :");
                    scanf("%d",&set1Rep);
                    printf("\nEnter representative of second set :");
                    scanf("%d",&set2Rep);
                    weightedUnion(set1Rep,set2Rep);
                    break;
                }
            case 6:
                {
                    int no;
                    printf("\nEnter number to find : ");
                    scanf("%d",&no);
                    printf("\n%d is parent",collapsingFind(no));
                    break;
                }
		}
	}
	free(setArr);
	free(setRep);
}
