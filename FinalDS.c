  /***********************************************************************
       PROJECT NAME : DICTIONARY OF UNUSUAL WORDS(CUSTOMIZABLE)
       OBJECTIVE    : IMPLEMENT A DICTIONARY USING BINARY SEARCH TREE
  ************************************************************************/


  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <windows.h>
  #include <dos.h>
  #include <dir.h>

  int i;  //global declarations


  void SetColor(int ForgC)  //function to generate text color
  {
      WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
      if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
      {
                 //Mask out all but the background attribute, and add in the foreground color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
      }
      return;
  }

  //structure declaration
  struct BSTnode {  //BINARY SEARCH TREE
        char word[128], meaning[256];
        struct BSTnode *left, *right;  //left and right elements of BST
  };

  //initialising structure variable
  struct BSTnode *root = NULL;   //initialising root to NULL

  //function to create new node and initialise its members
  struct BSTnode * createNode(char *word, char *meaning) {
        struct BSTnode *newnode;
        newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
        strcpy(newnode->word, word);  //insert the sttributes
        strcpy(newnode->meaning, meaning);
        newnode->left = newnode->right = NULL;
        return newnode;  //return pointer
  }

  //function to insert a given node into the BST at the appropriate position
  void insert(char *word, char *meaning) {
        struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
        int res = 0;
        if (!root) {  //if no element present in BST
                root = createNode(word, meaning);
                return;
        }
        for (current = root; current !=NULL;
           current = (res > 0) ? current->right : current->left) {
                res = strcasecmp(word, current->word);  //compare irrespective of character cases
                if (res == 0) {  //element already exists in the BST
                        SetColor(7);  // sets the output text color to LIGHT GRAY
                        printf("Duplicate entry!!\n");
                        return;
                }
                parent = current; //for next iteration
        }
        newnode = createNode(word, meaning);  //insert given node into appropriate position
        res > 0 ? (parent->right = newnode) : (parent->left = newnode);
        return;
  }

  //function to delete a given node from the BST
  void deleteNode(char *str) {
        struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
        int flag = 0, res = 0;
        if (!root) {  //if no element present in BST
                printf("BST is not present!!\n");
                return;
        }
        current = root;
        while (1) {
                res = strcasecmp(current->word, str);
                if (res == 0)
                        break;
                flag = res;
                parent = current;
                current = (res > 0) ? current->left : current->right; //conditional operator
                if (current == NULL){
                        SetColor(7);  // sets the output text color to LIGHT GRAY
                        printf("\n\t\tEntered word is not a part of the dictionary");
                        return;
                }

        }
        /* deleting leaf node */
        if (current->right == NULL) {
                if (current == root && current->left == NULL) {
                        free(current);
                        root = NULL;
                        return;
                }
                else if (current == root) {
                        root = current->left;  //make left child the root
                        free (current);
                        return;
                }

                flag > 0 ? (parent->left = current->left) :
                                (parent->right = current->left);
        }
        else {
                /* delete node with single child */
                temp = current->right;
                if (!temp->left) {
                        temp->left = current->left;
                        if (current == root) {
                                root = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (parent->left = temp) :
                                        (parent->right = temp);
                } else {
                        /* delete node with two children */
                        struct BSTnode *successor = NULL;
                        while (1) {
                                successor = temp->left;
                                if (!successor->left)
                                        break;
                                temp = successor;
                        }
                        temp->left = successor->right;
                        successor->left = current->left;
                        successor->right = current->right;
                        if (current == root) {
                                root = successor;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (parent->left = successor) :
                                        (parent->right = successor);
                }
        }
        free (current);
        return;
  }


  //function to search a given element in the BST
  void findElement(char *str) {
        struct BSTnode *temp = NULL;
        int flag = 0, res = 0;
        if (root == NULL) {
                printf("Binary Search Tree is out of station!!\n");
                return;
        }
        temp = root;
        while (temp) {
                if (strcasecmp(temp->word, str) == 0) {  //if the word is found
                        SetColor(11); // sets the output text color to LIGHT CYAN
                        printf("\n\t\tWord   : %s", str);
                        printf("\t\tMeaning: %s", temp->meaning);
                        flag = 1;
                        break;
                }
                temp = (strcasecmp(temp->word, str) > 0) ? temp->left : temp->right;
        }
        SetColor(7); // sets the output text color to LIGHT GRAY
        if (!flag)
                printf("\n\t\tEntered element not found in the dictionary\n");
        return;
  }

  //function that inserts predefined words into the dictionary(decided by the programmer)
  void add(){
        int i,j;
        char str[128], meaning[256];
        char *animals[5][30]={"Ahole\n","Nope\n","Leather tank\n","American murder log\n"};
        for(i=0;i<5;i++){
                for(j=0;animals[i][j]!='\0';j++){
                    strcpy(meaning,"Animal\n");  //initialise meaning to the concerned category
                    insert(animals[i][j],meaning); //insert the elements of the concerned category
                }
        }
        char *cities[5][30]={"Cando\n","Gogogogo\n","Oatmeal\n","Picnic\n"};
        for(i=0;i<5;i++){
                for(j=0;cities[i][j]!='\0';j++){
                    strcpy(meaning,"City\n");
                    insert(cities[i][j],meaning);
                }
        }
        char *colours[5][30]={"Gamboge\n","Arsenic\n","Cochineal\n","Brazilwood\n"};
        for(i=0;i<5;i++){
                for(j=0;colours[i][j]!='\0';j++){
                    strcpy(meaning,"colour\n");
                    insert(colours[i][j],meaning);
                }
        }
        char *Birds[5][30]={"Palila\n","Great Indian Bustard\n","Kakapo\n","Honduran Emerald\n"};
        for(i=0;i<5;i++){
                for(j=0;Birds[i][j]!='\0';j++){
                    strcpy(meaning,"Bird\n");
                    insert(Birds[i][j],meaning);
                }
        }
        char *Fruits[5][30]={"Cherimoya\n","Mangosteen\n","Jabuticaba\n","Ackee\n"};
        for(i=0;i<5;i++){
                for(j=0;Fruits[i][j]!='\0';j++){
                    strcpy(meaning,"Fruit\n");
                    insert(Fruits[i][j],meaning);
                }
        }
        char *vegetables[5][30]={"Durian\n","Jicama\n","Rambutan\n","Kohlrabi\n"};
        for(i=0;i<5;i++){
                for(j=0;vegetables[i][j]!='\0';j++){
                    strcpy(meaning,"vegetable\n");
                    insert(vegetables[i][j],meaning);
                }
        }
        char *Food[5][30]={"Sherbet\n","Gyro\n","Gravlax\n","Aioli\n"};
        for(i=0;i<5;i++){
                for(j=0;Food[i][j]!='\0';j++){
                    strcpy(meaning,"Food name\n");
                    insert(Food[i][j],meaning);
                }
        }
        char *Vehicles[5][30]={"Dacia\n","Fornasari\n","Zotye\n","AvtoVAZ\n"};
        for(i=0;i<5;i++){
                for(j=0;Vehicles[i][j]!='\0';j++){
                    strcpy(meaning,"Car name\n");
                    insert(Vehicles[i][j],meaning);
                }
        }
         char *profession[5][30]={"Ghost Hunter\n","Bride Kidnapping Expert\n","Bike Fishermen\n","Sales Ninja\n"};
        for(i=0;i<5;i++){
                for(j=0;profession[i][j]!='\0';j++){
                    strcpy(meaning,"Profession\n");
                    insert(profession[i][j],meaning);
                }
        }
        char *aquaticspecies[5][30]={"Kissing Loach\n","Sushi\n","Uncle Salmon\n","James Pond\n"};
        for(i=0;i<5;i++){
                for(j=0;aquaticspecies[i][j]!='\0';j++){
                    strcpy(meaning,"Aquatic species\n");
                    insert(aquaticspecies[i][j],meaning);
                }
        }

        char *insects[5][30]={"Damselfly\n","Silverfish\n","Aphid\n","Earwig\n"};
        for(i=0;i<5;i++){
                for(j=0;insects[i][j]!='\0';j++){
                    strcpy(meaning,"Insect\n");
                    insert(insects[i][j],meaning);
                }
        }
        char *dance[5][30]={"Mohiniyattam\n","Lion Dance\n","Kabuki\n","Fandango\n"};
        for(i=0;i<5;i++){
                for(j=0;dance[i][j]!='\0';j++){
                    strcpy(meaning,"Dance Form\n");
                    insert(dance[i][j],meaning);
                }
        }
        char *website[5][30]={"iloveyoulikeafatladylovesapples.com\n","heyyeyaaeyaaaeyaeyaa.com\n","nooooooooooooooo.com\n","omglasergunspewpewpew.com\n"};
        for(i=0;i<5;i++){
                for(j=0;website[i][j]!='\0';j++){
                    strcpy(meaning,"Website\n");
                    insert(website[i][j],meaning);
                }
        }
        char *virus[5][30]={"ILOVEYOU\n","Pikachu \n","slammer\n","Ping Pong\n"};
        for(i=0;i<5;i++){
                for(j=0;virus[i][j]!='\0';j++){
                    strcpy(meaning,"Computer virus\n");
                    insert(virus[i][j],meaning);
                }
        }
         char *brands[5][30]={"Givenchy\n","Bottega Veneta\n","Comme Des Garcons\n","Issey Miyake\n"};
        for(i=0;i<5;i++){
                for(j=0;brands[i][j]!='\0';j++){
                    strcpy(meaning,"Brand\n");
                    insert(brands[i][j],meaning);
                }
        }
         char *software[5][30]={"TrumpScript\n","Shakespeare\n","LOLCODE\n","Chicken\n"};
        for(i=0;i<5;i++){
                for(j=0;software[i][j]!='\0';j++){
                    strcpy(meaning,"Programming Language\n");
                    insert(software[i][j],meaning);
                }
        }
        char *medical[5][30]={"Walking Corpse Syndrome\n","Water Allergy\n","Tree Man Syndrome\n","Alien Hand Syndrome\n"};
        for(i=0;i<5;i++){
                for(j=0;medical[i][j]!='\0';j++){
                    strcpy(meaning,"Medical Condition\n");
                    insert(medical[i][j],meaning);
                }
        }
        char *music[5][30]={"Japanoise\n","Crunkcore\n","Pirate Metal\n","lowercase\n"};
        for(i=0;i<5;i++){
                for(j=0;music[i][j]!='\0';j++){
                    strcpy(meaning,"Music Genre\n");
                    insert(music[i][j],meaning);
                }
        }
        char *games[5][30]={"Tongue of the Fatman\n","Attack of the Mutant Camels\n","Ninja Hamster\n","Princess Tomato in Salad Kingdom\n"};
        for(i=0;i<5;i++){
                for(j=0;games[i][j]!='\0';j++){
                    strcpy(meaning," Video Game\n");
                    insert(games[i][j],meaning);
                }
        }
  }

  //function to display the BST in ascending order(inorder traversal : LVR)
  void inorderTraversal(struct BSTnode *myNode) {
        if (myNode) {

                inorderTraversal(myNode->left);  //recursive call
                SetColor(3);  // sets the output text color to CYAN
                printf("\t    %2d. %s",i++, myNode->word);
                inorderTraversal(myNode->right);  //recursive call
        }

        return;
  }

  int main() {
        int ch;
        char str[128], meaning[256];
        add();
        SetColor(2); // sets the output text color to GREEN
        printf("\n\t\t\t**********WELCOME**********\n\n");
        printf("\t     PRESENTING DICTIONARY OF UNUSUAL WORDS(CUSTOMIZABLE)\n\n");
        while (1) {
                SetColor(12);  // sets the output text color to LIGHT RED
                printf("\n\n\t\tPress 1 to display the dictionary \n");
                printf("\t\tPress 2 to search the meaning of any word\n");
                printf("\t\tPress 3 to insert a word of your choice(with meaning)\n");
                printf("\t\tPress 4 to delete a word from the dictionary\n");
                printf("\t\tPress 5 to exit\n\n\t\tEnter ur choice:");
                scanf("%d", &ch);
                getchar();
                switch (ch) {
                        case 1:
                                i=1;
                                SetColor(11);  // sets the output text color to LIGHT CYAN
                                printf("\n\n\t\tThe words in the dictionary are:\n");
                                inorderTraversal(root);  //to display the BST
                                break;
                        case 2:
                                printf("\n\t\tEnter the search word : ");
                                fgets(str, 100, stdin); //input the string
                                findElement(str);  // call findElement(str)
                                break;
                        case 3:
                                printf("\n\t\tEnter the word to insert : ");
                                fgets(str, 100, stdin);  //input the string
                                printf("\t\tMeaning : ");
                                fgets(meaning, 256, stdin);
                                insert(str, meaning);
                                break;
                        case 4:
                                printf("\n\t\tEnter the word to delete:");
                                fgets(str, 100, stdin);  //input the string
                                deleteNode(str);
                                break;
                        case 5:
                                SetColor(5);
                                printf("\n\t\t\t Terminating !!!!");
                                exit(0);
                        default:
                                SetColor(7);
                                printf("\t\t\tYou have entered wrong option\n");
                                break;
                }
        }
        return 0;
  }
