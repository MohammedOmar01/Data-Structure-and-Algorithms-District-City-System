#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 100
#define TABLE_SIZE 23

typedef struct node Node;
typedef Node* ptr;
struct node {
    char district[MAX_STR];                       //========Mohammad omar========//
    char town[MAX_STR];                              //========1212429========//
    int population;
    int elevation;
    char hasMunicipality[5];            //struct for AVL tree
    ptr left;
    ptr right;
    int height;
};
//////////////////////////////////////////////////////////////////////////////////////
typedef struct nodeHash {
    char key[6];
    char district[MAX_STR];
    char town[MAX_STR];                // Struct for hash table
    int population;
    int elevation;
    char hasMunicipality[5];
    int occupied;
} NodeHash;
NodeHash hashTable[TABLE_SIZE];
int currentSize = 0;
//////////////////////////////////////////////////////////////////////////////////////
ptr make_empty(ptr T);                       // make empty function for AVL
ptr read_File(ptr root, char* filename);     // read file function
ptr insertAVL(ptr T,char district[],char town[],int population, int elevation,char hasMunicipality[]);
ptr findAVL(ptr T,char* townKey);            // find a node in AVL tree
ptr deleteAVL(ptr T,char* townKey);          // delete any node in AVL tree
void inOrder(ptr T);                         // inOrder print for AVL
void list_grater_pop(ptr T, int popLimit);   // list grater population
void list_Municipality(ptr T,char* yes_no);  // list municipality
void updateAVL(ptr node, int newPopulation, int newElevation,char* newMunicipality);
int height_avl(ptr N);                       // determine the high of the tree
int maxVal(int a, int b);                    // max between tow number to update the high
ptr singleRotateLeft(ptr K2);                // single left routate
ptr singleRotateRight(ptr K1);               // single right routate
ptr doubleRotateLeft(ptr K3);                // double left right routate
ptr doubleRotateRight(ptr K1);               // double right left routate
ptr findMinAVL(ptr T);                       // find the min node if we need to delete
void write_File(ptr root,char* filename);    // write on file function
void initHashTable();                        // make a hash table function
int insertHash(char* district,char* town, int population, int elevation, char* hasMuni);
int searchHash(char* town);                  // search on specific value
void deleteHash(char* town);                 // delete from hash table
void printHash();                            // function to print a hash
void state_hash();                           // function to implement the state of the hash
void build_hash(char* filename);
void save_hash(char* filename);
void getKey( char* town, char* keyBuffer);
int hashFunction( char* key);
/////////////////////////////////////////////========THE MAIN========/////////////////////////////////////////////////////
int main() {
    ptr root = NULL;
    root = make_empty(root);
    root = read_File(root, "districts.txt");
    int choice;
    do {
                printf("\n----------------- AVL/Town Menu -----------------\n");
                printf("1. Insert a new town\n");
                printf("2. Find and update a town\n");
                printf("3. List all towns\n");
                printf("4. List towns with population > X\n");
                printf("5. List towns that have or not have municipalities\n");
                printf("6. Delete a town\n");
                printf("7. Save all information to 'towns.txt'\n");
                printf("8. Build Linear Hash Table\n");
                printf("0. Exit\n");
                printf("Choose an option: ");
                scanf("%d", &choice);
                getchar();
        switch (choice) {
            case 1: {
                                                                  // Enter 1 for Insert a new town
                char district[MAX_STR];
                char town[MAX_STR];
                int population, elevation;
                char hasMuni[5];
                printf("Enter district: ");
                fgets(district, sizeof(district), stdin);
                district[strcspn(district, "\r\n")] = 0;
                printf("Enter town: ");
                fgets(town, sizeof(town), stdin);
                town[strcspn(town, "\r\n")] = 0;
                printf("Enter population: ");
                scanf("%d", &population);
                printf("Enter elevation: ");
                scanf("%d", &elevation);
                getchar();
                printf("Has municipality?");
                fgets(hasMuni, sizeof(hasMuni), stdin);
                hasMuni[strcspn(hasMuni, "\r\n")] = 0;
                root = insertAVL(root, district, town, population, elevation, hasMuni);
                printf("Town '%s' inserted.\n", town);
                break;
            }
            case 2: {
                                                                     // Enter 2 to Find and update a town
                char searchTown[MAX_STR];
                printf("Enter town name to find: ");
                fgets(searchTown, sizeof(searchTown), stdin);
                searchTown[strcspn(searchTown, "\r\n")] = 0;
                ptr found = findAVL(root, searchTown);
            if (found == NULL) {
                printf("Town '%s' not found.\n", searchTown);
             } else {
                printf("Found town '%s'. Current info:\n", found->town);
                printf("District: %s | Population: %d | Elevation: %d | Municipality: %s\n",
                found->district, found->population, found->elevation, found->hasMunicipality);
                int newPop, newElev;
                char newMuni[5];
                printf("Enter new population: ");
                scanf("%d", &newPop);
                printf("Enter new elevation: ");
                scanf("%d", &newElev);
                getchar();
                printf("has municipality? (yes/no) in Capital please: ");
                fgets(newMuni, sizeof(newMuni), stdin);
                newMuni[strcspn(newMuni, "\r\n")] = 0;
                updateAVL(found, newPop, newElev, newMuni);
                printf("Town '%s' updated ^_^\n", searchTown);
                }
                break;
            }
            case 3: {
                                                                 // Enter 3 to List all towns in alphabetical order
                printf("\n--- All Towns (In-Order) ---\n");
                inOrder(root);
                break;
            }
            case 4: {
                                                                 // Enter 4 List towns with population > X
                int limit;
                printf("Enter population limit: ");
                scanf("%d", &limit);
                getchar();
                printf("\nTowns with population > %d:\n", limit);
                list_grater_pop(root, limit);
                break;
            }
            case 5: {
                                                                 // Enter 5 to  List towns that have or not have municipality
                char muniChoice[5];
                printf("Enter 'yes or no ' to list towns names that have municipality\n");
                fgets(muniChoice, sizeof(muniChoice), stdin);
                muniChoice[strcspn(muniChoice, "\r\n")] = 0;
                list_Municipality(root, muniChoice);
                break;
            }
            case 6: {
                                                                  // Enter 6 to Delete a town
                char delTown[MAX_STR];
                printf("Enter town name to delete: ");
                fgets(delTown, sizeof(delTown), stdin);
                delTown[strcspn(delTown, "\r\n")] = 0;
                root = deleteAVL(root, delTown);
                printf("Town '%s' deleted ^_^ \n", delTown);
                break;
            }
            case 7: {
                                                                   // Enter 7 to Save all data to file
                write_File(root, "towns.txt");
                printf("data saved to towns.txt \n");
                break;
            }
            case 8: {
                                                                    // Enter 8 Build linear hash table that read from the output file of AVL
                initHashTable();
                 build_hash("towns.txt");
                printf("\nLinear Hash Table built from 'towns.txt'.\n");
                int hashChoice;
                do {
                    printf("\n--- Hash Table Menu (Linear Probing) ---\n");
                    printf("1. Print entire hash table\n");
                    printf("2. Print size/load factor\n");
                    printf("3. Insert a new record\n");
                    printf("4. Search for a specific town\n");
                    printf("5. Delete a specific record\n");
                    printf("6. Save data back to 'towns.txt'\n");
                    printf("0. Back to AVL Menu\n");
                    printf("Choose an option: ");
                    scanf("%d", &hashChoice);
                    getchar();

                    switch (hashChoice) {
                        case 1: {
                            printHash();
                            break;
                        }
                        case 2: {
                            state_hash();
                            break;
                        }
                        case 3: {
                            char district[MAX_STR], newTown[MAX_STR], hasMuni[5];
                            int population, elevation;

                            printf("Enter district: ");
                            fgets(district, sizeof(district), stdin);
                            district[strcspn(district, "\r\n")] = 0;

                            printf("Enter town: ");
                            fgets(newTown, sizeof(newTown), stdin);
                            newTown[strcspn(newTown, "\r\n")] = 0;

                            printf("Enter population: ");
                            scanf("%d", &population);
                            printf("Enter elevation: ");
                            scanf("%d", &elevation);
                            getchar();

                            printf("Has municipality? (yes/no): ");
                            fgets(hasMuni, sizeof(hasMuni), stdin);
                            hasMuni[strcspn(hasMuni, "\r\n")] = 0;

                            int col = insertHash(district, newTown, population, elevation, hasMuni);
                            if (col >= 0) {
                                printf("Inserted '%s' with %d collisions.\n", newTown, col);
                            }
                            break;
                        }
                        case 4: {
                            char findTown[MAX_STR];
                            printf("Enter town name: ");
                            fgets(findTown, sizeof(findTown), stdin);
                            findTown[strcspn(findTown, "\r\n")] = 0;
                            searchHash(findTown);
                            break;
                        }
                        case 5: {
                            char delTown2[MAX_STR];
                            printf("Enter town name to delete: ");
                            fgets(delTown2, sizeof(delTown2), stdin);
                            delTown2[strcspn(delTown2, "\r\n")] = 0;
                            deleteHash(delTown2);
                            break;
                        }
                        case 6: {

                            save_hash("towns.txt");

                            break;
                        }
                        case 0: {
                            break;
                        }
                        default: {
                            printf("invalid choice in hash menu. \n");
                            break;
                        }
                    }
                } while (hashChoice != 0);
                break;
            }
            case 0: {

                break;
            }
            default: {
                printf("Invalid choice (AVL menu). Try again.\n");
                break;
            }
        }

    }
     while (choice != 0);
      root = make_empty(root);
    return 0;
}

////////////////////////////========/AVL FUNCTIONS/=========////////////////////////////////////////////
ptr make_empty(ptr T) {             // A function to make the AVL empty by Recursion
    if (T != NULL) {                  // its go to every leaf node first and free it
       make_empty(T->left);
       make_empty(T->right);
        free(T);
    }
    return NULL;
}
//////////////////////////////////////////////////////////////////////////
int height_avl(ptr N) {               // A function to determine the hight of each node
    if (N == NULL) {
        return -1;
    }
    return N->height;
}
//////////////////////////////////////////////////////////////////////////
int maxVal(int a, int b) {           // This function is related to the hight , that will give us the bigger number between tow hight by also recursion (we will dissus it later)
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
//////////////////////////////////////////////////////////////////////////
ptr singleRotateLeft(ptr K2) {      // function to make a Single rotate Left (if there is a issue in the hight)
    if (K2 == NULL) {
        return NULL; // safety check
    }
    ptr K1 = K2->left;
    if (K1 == NULL) {
        return K2;   // no left child, can't rotate
    }
       K2->left = K1->right;
       K1->right = K2;
       K2->height = maxVal(height_avl(K2->left), height_avl(K2->right)) + 1;
       K1->height = maxVal(height_avl(K1->left), height_avl(K2)) + 1;
    return K1;
}
//////////////////////////////////////////////////////////////////////////
ptr singleRotateRight(ptr K1) {    // The same here ( single rotate but for the right ) the same as the prevuse function

    if (K1 == NULL) {
        return NULL;  // safety check
    }
       ptr K2 = K1->right;
    if (K2 == NULL) {
        return K1;   // no right child , can't rotate
    }
       K1->right = K2->left;
       K2->left = K1;
       K1->height = maxVal(height_avl(K1->left), height_avl(K1->right)) + 1;
       K2->height = maxVal(height_avl(K2->right), height_avl(K1)) + 1;
    return K2;
}
//////////////////////////////////////////////////////////////////////////
ptr doubleRotateLeft(ptr K3) {    // A function to do a Double rotate left (Left-Right)
    if (K3 == NULL) {
        return NULL;
    }
    if (K3->left != NULL) {
       K3->left = singleRotateRight(K3->left);
    }
    return singleRotateLeft(K3);
}
//////////////////////////////////////////////////////////////////////////
ptr doubleRotateRight(ptr K1) {   // A function to do a Double rotate right (Right-Left)
    if (K1 == NULL) {
        return NULL;
    }
    if (K1->right != NULL) {
       K1->right = singleRotateLeft(K1->right);
    }
    return singleRotateRight(K1);
}
//////////////////////////////////////////////////////////////////////////
ptr findMinAVL(ptr T) {       // Function to find the minimum value in the avl tree but after he fix the high and the value or just a test
    if (T == NULL) {          // the minimum value will be on the left side , so we need to go to the value that its in extreme left
        return NULL;          // side of the tree , and we just call a recursion to the left value every time and check
    }                         // and check if the value that it is left is it null or not , if yes , so its a leaf node and this node its extramly left so its the minimum value
    else if (T->left == NULL) {
        return T;
    }
    else {
        return findMinAVL(T->left);
    }
}
//////////////////////////////////////////////////////////////////////////
ptr insertAVL(ptr T,char district[], char town[],int population, int elevation, char hasMunicipality[]) {
    if (T == NULL) {
        T = (ptr)malloc(sizeof(Node));
        if (T == NULL) {
            printf("Out of memory\n");
            return NULL;
        }                                               // Function to insert a new node in the tree lets see who its work
        strcpy(T->district, district);                  // so is the main loop in the case statment number 1 we make the user enter a district and town and population and elevation and the municipality
        strcpy(T->town, town);                          // firstly we assume that the tree node is null , and if its null then start our function by copy char string of municipality and district and town by strcpy function and put them in there please in tree
        T->population = population;                     // since the population and evalutaion are a number , so we need only to point the plase of them in the tree and put the user entry
        T->elevation = elevation;                       // assign the left and right of the node to be null since we need to insert it later and the hight is zero since its just a node
        strcpy(T->hasMunicipality, hasMunicipality);
        T->left = NULL;
        T->right = NULL;
        T->height = 0;
    }
    else {
        int cmp = strcmp(town, T->town);
        if (cmp < 0) {
            T->left = insertAVL(T->left, district, town, population, elevation, hasMunicipality);
            if ((height_avl(T->left) - height_avl(T->right)) == 2) {
                if (strcmp(town, T->left->town) < 0) { // ok if the node is not null , we use the strcmp to compare the value of the town since the town is out key here
                    T = singleRotateLeft(T);           // if the user town is less than the town we are in (since strcmp gives a value of 1 -1 0 ) so we need to go left and go back another time to check , since we need a place for the user depend on the town
                } else {                               // then just in case to make our avl an valid we check the hight of the left and the right and according to out town and the node in left after out town if its less then it will be a single root for left , if any think else then it will be double rotation
                    T = doubleRotateLeft(T);
                }
            }
        }
        else if (cmp > 0) {
            T->right = insertAVL(T->right, district, town, population, elevation, hasMunicipality);
            if ((height_avl(T->right) - height_avl(T->left)) == 2) {
                if (strcmp(town, T->right->town) > 0) {
                    T = singleRotateRight(T);         // the same think but know if the user town is bigger than the currant town
                } else {                              // so we need to insert this town to the right and check to the valid of the AVL by mauaring the hight
                    T = doubleRotateRight(T);
                }
            }
        }

    }
    T->height = maxVal(height_avl(T->left),height_avl(T->right)) + 1;
    return T;
}
//////////////////////////////////////////////////////////////////////////
ptr findAVL(ptr T, char* townKey) {     // A function to search on a node by town name we need this function later on to case 2
    if (T == NULL) {
        return NULL;
    }
    int cmp = strcmp(townKey, T->town);
    if (cmp < 0) {                         // by taking the town name from user then search on it in the tree who ? by compare the tow town
        return findAVL(T->left, townKey);  // like we said in the insert part , if the strcmp function not 1 of -1 then its 0 so we find it and return the node T
    }
    else if (cmp > 0) {
        return findAVL(T->right, townKey);
    }
    else {
        return T;
    }
}
//////////////////////////////////////////////////////////////////////////
ptr deleteAVL(ptr T,char* townKey) {      // function to Delete by town key from user
    if (T == NULL) {
        return NULL;
    }
    int cmp = strcmp(townKey, T->town);                  // the same think here , we compare the tow town and when the strcmp give us a zero result so its the node that contane the town that the user need to delete
    if (cmp < 0) {                                       // when we find it we have 4 cases , first if the node is leaf node , so we free it noramlly
        T->left = deleteAVL(T->left, townKey);           // case 2 if the left side of the node contain another node , and the right are a null so we need to make a temp pointer to point on the right side then free our node , then resolve the t to the temp value of or the right .
    }                                                    // case 3 it the same as case 2 but the right side contain a node and left is null
    else if (cmp > 0) {                                  // case 4 if the node contain a node from left and right and find the smallest node on the right side (case delete)
        T->right = deleteAVL(T->right, townKey);         // when we find it just put it on a temp value pinter and copy every think from it to make a switch between the less value of the right sub tree the currant node
    }                                                    // then make the recartion another time to the user town chooes
    else {                                               // after we finsh deleting what we need , we need to make the AVL valid another time by measuring the hight and do the single and double rotate thhat we discuse it prevesly

        if (T->left == NULL && T->right == NULL) {
            free(T);
            return NULL;
        }
        else if (T->left == NULL) {
            ptr tmp = T->right;
            free(T);
            T = tmp;
        }
        else if (T->right == NULL) {
            ptr tmp = T->left;
            free(T);
            T = tmp;
        }
        else {
            ptr tmp = findMinAVL(T->right);
            strcpy(T->town, tmp->town);
            strcpy(T->district, tmp->district);
            T->population = tmp->population;
            T->elevation = tmp->elevation;
            strcpy(T->hasMunicipality, tmp->hasMunicipality);
            T->right = deleteAVL(T->right, tmp->town);
        }
    }
    if (T != NULL) {
        T->height = maxVal(height_avl(T->left), height_avl(T->right)) + 1;
        int balance = height_avl(T->left) - height_avl(T->right);
        if (balance == 2) {
            if (height_avl(T->left->left) >= height_avl(T->left->right)) {
                T = singleRotateLeft(T);
            } else {
                T = doubleRotateLeft(T);
            }
        }
        else if (balance == -2) {
            if (height_avl(T->right->right) >= height_avl(T->right->left)) {
                T = singleRotateRight(T);
            } else {
                T = doubleRotateRight(T);
            }
        }
    }
    return T;
}
//////////////////////////////////////////////////////////////////////////
void inOrder(ptr T) {      // Function to print the AVL tree In order print (left root right)
    if (T != NULL) {
        inOrder(T->left);
        printf("Town: %s | District: %s | Population: %d | Elevation: %d | Municipality: %s\n", T->town, T->district, T->population, T->elevation, T->hasMunicipality);
        inOrder(T->right);
    }
}
//////////////////////////////////////////////////////////////////////////
void list_grater_pop(ptr T, int popLimit) {//Function to List towns with population > limit
    if (T != NULL) {
        list_grater_pop(T->left, popLimit);                               // we take the root of the tree and start to search on a node that
        if (T->population > popLimit) {                                   // contain a population bigger than the user population need
            printf("Town: %s | Population: %d\n", T->town, T->population);// so its we need the bigger , then we need to search on the right side of tree by recursion
        }                                                                 // if we find it just print it , till the node is null
        list_grater_pop(T->right, popLimit);
    }
}
//////////////////////////////////////////////////////////////////////////
void list_Municipality(ptr T,char* yes_no) {                            //function to town that List by municipality yes/no */
    if (T != NULL) {
        list_Municipality(T->left, yes_no);                            // the same here but we need to search in all the tree till the strcmp function is zero while compare Municipality
        if (strcmp(T->hasMunicipality, yes_no) == 0) {                 // of the node we are on it with yes or no string from user
            printf("Town: %s| Municipality: %s\n", T->town,T->hasMunicipality);
        }
        list_Municipality(T->right, yes_no);
    }
}
//////////////////////////////////////////////////////////////////////////
void updateAVL(ptr node, int newPopulation, int newElevation, char* newMunicipality) {
    if (node != NULL) {                                  // Function to update a nodes population, elevation and municipality
        node->population = newPopulation;
        node->elevation = newElevation;
        strcpy(node->hasMunicipality, newMunicipality);
    }
}
//////////////////////////////////////////////////////////////////////////
ptr read_File(ptr root,char* filename) { // Function to Read from  file districts.txt and insert all information in each line in a node
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return root;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        char district[MAX_STR], town[MAX_STR];
        int population, elevation;
        char hasMuni[5];
        sscanf(buffer, "%[^:]:%[^:]:%d:%d:%s", district, town, &population, &elevation, hasMuni);
        root = insertAVL(root, district, town, population, elevation, hasMuni);
    }
    fclose(fp);
    return root;
}
//////////////////////////////////////////////////////////////////////////
void inOrderWriteAVL(ptr node, FILE* fp) {             // function to in-order write to file output
    if (node != NULL) {
        inOrderWriteAVL(node->left, fp);
        fprintf(fp, "%s:%s:%d:%d:%s\n", node->district, node->town, node->population, node->elevation, node->hasMunicipality);
        inOrderWriteAVL(node->right, fp);
    }
}
//////////////////////////////////////////////////////////////////////////
void write_File(ptr root, char* filename) {     // function to Write the AVL tree to a file
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return;
    }
    inOrderWriteAVL(root, fp);
    fclose(fp);
}
///////////////////////////======/HASH FUNCTION (LINEAR HASHING)/========/////////////////////////////////////////////
void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {   // This function sets up the  global hash table by asign all its slots as unoccupied and clearing any existing keys
        hashTable[i].occupied = 0;           // it also resets the current size of the hash table to zero, indicating that its empty
        hashTable[i].key[0] = '\0';
    }
    currentSize = 0;
}
//////////////////////////////////////////////////////////////////////////
void getKey(char* town, char* keyBuffer) {  // function to get the key by taken the first 5 litter of the town name and put them in the key buffer
    strncpy(keyBuffer, town, 5);
    keyBuffer[5] = '\0';
}
//////////////////////////////////////////////////////////////////////////
int hashFunction(char* key) {              // This hash function calculates the sum of the ASCII values of all characters in the string key the first 5 litter
    int sum = 0;                           // and then takes the modulo with TABLE_SIZE to ensure the hash value fits within the bounds of the hash table.
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}
//////////////////////////////////////////////////////////////////////////
int insertHash(char* district, char* town, int population, int elevation,  char* hasMuni) {
    if (currentSize == TABLE_SIZE) {
        printf("Table is FULL. Cannot insert '%s'\n", town);
        return -1;
    }                                                 // the main function here is to Insert by using using linear probing
    char key[6];                                      // it inserts a record into a hash table using linear probing for collision resolution. It calculates the index using a hash function that we discipe previously
    getKey(town, key);                                // then iteratively checks for the next available slot if a collision occurs
     int index = hashFunction(key);                   // once a free or previously deleted slot is found, it inserts the data and updates the tables occupancy status and If the table is full or no free slot is available after probing, the function returns an error.
     int startIndex = index;
    int collisions = 0;
    while (1) {
        if (hashTable[index].occupied == 0 || hashTable[index].occupied == 2) {
            strcpy(hashTable[index].key, key);
            strcpy(hashTable[index].district, district);
            strcpy(hashTable[index].town, town);
            hashTable[index].population = population;
            hashTable[index].elevation = elevation;
            strcpy(hashTable[index].hasMunicipality, hasMuni);
            hashTable[index].occupied = 1;
            currentSize++;
            return collisions;
        }
        collisions++;
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            printf("No free slot found for the town :  '%s'\n", town);
            return -1;
        }
    }
}
//////////////////////////////////////////////////////////////////////////
int searchHash(char* town) {                             // this function searches for a record in a hash table using linear probing
    char key[6];                                         // It generates a key for the input town and calculates the starting index with the hash function. The function then iterates through the table
    getKey(town, key);                                   // checking if the slot is occupied and matches both the key and the town name. If found, it prints the number of collisions and returns the index
     int index = hashFunction(key);                      // If it encounters an empty slot or loops back to the start without finding the town, it concludes the town is not present and returns -1
     int startIndex = index;
    int collisions = 0;

    while (hashTable[index].occupied != 0) {
        if (hashTable[index].occupied == 1 &&
            strcmp(hashTable[index].key, key) == 0 &&
            strcmp(hashTable[index].town, town) == 0)
        {
            printf("Found '%s' after %d collisions.\n", town, collisions);
            return index;
        }
        collisions++;
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            break;
        }
    }
    printf("Town '%s' is not found, Collisions=%d\n", town, collisions);
    return -1;
}
//////////////////////////////////////////////////////////////////////////
void deleteHash(char* town) {                               //function to delete a an town from the hash table
    int idx = searchHash(town);
    if (idx == -1) {
        return;
    }
    hashTable[idx].occupied = 2;
    currentSize--;
    printf("Town '%s' deleted\n", town);
}
//////////////////////////////////////////////////////////////////////////
void printHash() {
    printf("\n-------------------------------- HASH TABLE --------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);                                // function to print all the hash table including the empty spot
        if (hashTable[i].occupied == 1) {
            printf("KEY='%s' TOWN='%s' DISTRICT='%s' POPU=%d ELEV=%d MUNI=%s\n", hashTable[i].key,hashTable[i].town,hashTable[i].district,hashTable[i].population,hashTable[i].elevation,hashTable[i].hasMunicipality);}
        else if (hashTable[i].occupied == 2) {
            printf("DELETED\n");
        }
        else {
            printf("EMPTY\n");
        }
    }
}
//////////////////////////////////////////////////////////////////////////
void state_hash() {
    double loadFactor = currentSize / (double)TABLE_SIZE;  // function to print the load factor and the size and also the slots that taken in the hash

    printf("\nHash Table Size: %d\n", TABLE_SIZE);
    printf("slots thats taken: %d\n", currentSize);
    printf("Load Factor:%f\n", loadFactor);
}
//////////////////////////////////////////////////////////////////////////
void build_hash(char* filename) {                 // a function to get read from the output file of the AVL , and buld a hash table
    FILE* fp = fopen(filename, "r");                     // line by line and every line go to the insert function
    if (fp == NULL) {
        printf("Could not open '%s' for reading\n", filename);
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        char district[MAX_STR], htown[MAX_STR];
        int population, elevation;
        char hasMuni[5];
        sscanf(buffer, "%[^:]:%[^:]:%d:%d:%s", district, htown, &population, &elevation, hasMuni);
        insertHash(district, htown, population, elevation, hasMuni);
    }
    fclose(fp);
}
//////////////////////////////////////////////////////////////////////////
void save_hash(char* filename) {                     // function to save the hash table to the file output
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file '%s' ^_^\n", filename);
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].occupied == 1) {
            fprintf(fp, "%s:%s:%d:%d:%s\n", hashTable[i].district, hashTable[i].town, hashTable[i].population,hashTable[i].elevation,hashTable[i].hasMunicipality);
        }
    }
    fclose(fp);
    printf("Hash table data saved back to the file %s  \n", filename);

}
