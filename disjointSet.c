#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int parent[100];

int root(int);
void makeSet(int);
int find(int, int);
void unionSet(int, int);

void main() {
	int choice, subSet, element1, element2;
	do {
		printf("\n1.Make set\n2.Union operation\n3.Find operation\n4.Exit\nEnter your choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: printf("\nEnter number of subsets to be created: ");
				scanf("%d", &subSet);
				makeSet(subSet);
				break;
			case 2: printf("\nEnter the two subsets to do union: ");
				scanf("%d", &element1);
				scanf("%d", &element2);
				unionSet(element1, element2);
				break;
			case 3: printf("\nEnter the two elements to find if they are related: ");
				scanf("%d", &element1);
				scanf("%d", &element2);
				int root = find(element1, element2);
				if(root == -1)
					printf("\nThey do not have same roots\n");
				else 
					printf("The root of %d, and %d is %d", element1, element2, root);
				break;
			case 4: exit(0);
			default: printf("\nEntered the wrong choice !!!!!\n");
		}
	}while(choice != 4);
}

//Method for making subsets
void makeSet(int elements) {
	for (int i = 0; i < elements; i++) {
		parent[i] = i;
	}
}

//Method to find root
int root(int subSet) {
	while (parent[subSet] != subSet) {
		subSet = parent[subSet];
	}
	return subSet;
} 

//Method to union the subsets
void unionSet(int a ,int b) {
	int rootA = root(a);
	int rootB = root(b);
	parent[rootA] = rootB;	//Setting parent of root(a) as root(b)
}	

//Mehtod for find
int find(int a, int b) {
	int rootFind;
	if(root(a) == root(b)) {
		rootFind = root(a);
		return rootFind;
	}
	else
		return -1;
}
