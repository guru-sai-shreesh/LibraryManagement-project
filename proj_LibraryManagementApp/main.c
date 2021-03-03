//
//  main.c
//  library management app
//
//  Created by Guru sai shreesh Tirumalla.
//

// proj completed but doubts about getchar()

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 60
#define C 6

bool category[C][N];//tracks books under categeoru
/* There are 7 categorys of books namely:
 1. "Computer" [0]
 2. "Electrical" [1]
 3. "Civil" [2]
 4. "Mechnnical" [3]
 5. "Maths" [4]
 6. "Space" [5]
 */

char cat_name[C][11]={"Computer", "Electrical", "Civil", "Mechnnical", "Maths", "Space"};

typedef struct{
    char book_name[50];
    char author_name[30];
    int book_id;
    int quantity;
    int rack_no;
    int category;
    long int book_prize;
    int lendingPrize_week;
} book;

book books[N];// Assuming max limit of unique kind of books are 60
int last = 0;

bool strbkcmp(char*, char*);

void incDefault_books(void);
void search_Bname(void);
void search_Bid(void);
void search_Bcat(void);
void search_Aname(void);

void add_book(void);
void incrdec_qty_book(void);
int total_quantity(void);
void print_bookNameId(void);
void rmvbook_id(void);


int main() {
    for (int i=0; i<N-1; i++) {//sets book id's
        books[i].book_id= 1000+(i*10);
        books[i].quantity= 20;
    }
    incDefault_books();
    int logopt;
login:
    printf("*************************************************\n");
    printf("********************* LOGIN *********************\n\n");
    printf("Enter 1 if you are a student\n");
    printf("Enter 2 if you are librarian\n");
    printf("Enter 3 to quit\n");
    int c=0;
    do {
        if(c>0){
            printf("Enter valid option!!!\n");
        }
        printf("Enter your option: ");
        scanf("%d", &logopt);
        c++;
    } while (logopt!=1 && logopt!=2 && logopt!=3);
    if(logopt==1){//student login
        while(1){
            int opt;
            printf("\n");
            printf("*************************************************\n");
            printf("******************* MAIN MENU *******************\n\n");
            printf("To locate the book in library search book using below methods\n");
            printf("Enter 1 to search using Book name\n");
            printf("Enter 2 to search using Book id\n");
            printf("Enter 3 to search using categeory\n");
            printf("Enter 4 to search using Author name\n");
            printf("Enter 5 to go back to login\n");
            printf("Enter 6 to quit\n");
            printf("\n");
        studentlog_opt:
            printf("Enter your option: ");
            scanf("%d", &opt);
            switch (opt) {
                case 1:
                    search_Bname();
                    break;
                case 2:
                    search_Bid();
                    break;
                case 3:
                    search_Bcat();
                    break;
                case 4:
                    search_Aname();
                    break;
                case 5:
                    goto login;
                    break;
                case 6:
                    return 0;
                    break;
                    
                default:
                    printf("Enter correct valid opt!!!\n");
                    goto studentlog_opt;
                    break;
            }
        }
    }
    else if (logopt==2){//Librarian login
        char usr_id[15];
        char pass[15];
        int er=0;
        do {
            if (er>0) {
                printf("Enter correct creditials!!!\n");
            }
            printf("Enter user id: ");
            scanf("%s", usr_id);
            printf("Enter password: ");
            scanf("%s", pass);
            er++;
        } while (strcmp(usr_id, "gurufeb04")!=0 && strcmp(pass, "143")!=0 && er<3);
        if (strcmp(usr_id, "gurufeb04")==0 && strcmp(pass, "143")==0) {
            while (1) {
                int opt;
                printf("\n");
                printf("*************************************************\n");
                printf("******************* MAIN MENU *******************\n\n");
                printf("Enter 1 to add book\n");
                printf("Enter 2 to increase or decrease quantity of book\n");
                printf("Enter 3 to check total number of books in library\n");
                printf("Enter 4 to display book names with their book id's\n");
                printf("Enter 5 to remove book using book id\n");
                printf("Enter 6 to go back to login\n");
                printf("Enter 7 to quit\n");
                printf("\n");
            librarianlog_opt:
                printf("Enter your option: ");
                scanf("%d", &opt);
                switch (opt) {
                    case 1:
                        add_book();
                        break;
                    case 2:
                        incrdec_qty_book();
                        break;
                    case 3:
                        total_quantity();
                        break;
                    case 4:
                        print_bookNameId();
                        break;
                    case 5:
                        rmvbook_id();
                        break;
                    case 6:
                        goto login;
                        break;
                    case 7:
                        return 0;
                        break;
                            
                    default:
                        printf("Enter correct valid opt!!!\n");
                        goto librarianlog_opt;
                        break;
                }
            }
        }
        else{
            printf("You ran out of trials\n");
            printf("Redirecting to common login.........\n");
            goto login;
        }
    }
    else if (logopt==3){
        return 0;
    }
}

void incDefault_books(){//this function defines 16 books
    // the data in structures is'nt statically initialized becoz book id's are not created manually
    strcpy(books[last].author_name, "Yashavant Kanetkar");
    strcpy(books[last].book_name, "Let Us C");
    books[last].book_prize = 247;
    books[last].lendingPrize_week = 7;
    books[last].rack_no = 2;
    books[last].category = 0;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "Thomas H. Cormen");
    strcpy(books[last].book_name, "Introduction to algorithms");
    books[last].book_prize = 6625;
    books[last].lendingPrize_week = 32;
    books[last].rack_no = 1;
    books[last].category = 0;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "Narasimha Karumanchi");
    strcpy(books[last].book_name, "Data Structures and Algorithms Made Easy");
    books[last].book_prize = 657;
    books[last].lendingPrize_week = 9;
    books[last].rack_no = 2;
    books[last].category = 0;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "Book by B.L. Theraja");
    strcpy(books[last].book_name, "Text Book of Electrical Technology");
    books[last].book_prize = 1781;
    books[last].lendingPrize_week = 17;
    books[last].rack_no = 1;
    books[last].category = 1;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "Rohit Mehta");
    strcpy(books[last].book_name, "Objective Electrical Technology");
    books[last].book_prize = 733;
    books[last].lendingPrize_week = 8;
    books[last].rack_no = 2;
    books[last].category = 1;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "B.N. Dutta");
    strcpy(books[last].book_name, "Estimating and Costing in Civil Engineering");
    books[last].book_prize = 620;
    books[last].lendingPrize_week = 9;
    books[last].rack_no = 1;
    books[last].category = 2;
    category[books[last].category][last]=true;
    last++;

    strcpy(books[last].author_name, "K. Subramanya");
    strcpy(books[last].book_name, "Engineering Hydrology");
    books[last].book_prize = 610;
    books[last].lendingPrize_week=9;
    books[last].rack_no = 2;
    books[last].category = 2;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "J.K. Gupta");
    strcpy(books[last].book_name, "Theory of Machines");
    books[last].book_prize = 650;
    books[last].lendingPrize_week = 9;
    books[last].rack_no = 1;
    books[last].category = 3;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "V. B. Bhandari");
    strcpy(books[last].book_name, "Design of Machine Elements");
    books[last].book_prize = 715;
    books[last].lendingPrize_week = 10;
    books[last].rack_no = 1;
    books[last].category = 3;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "Erwin Kreyszig");
    strcpy(books[last].book_name, "Advanced Engineering Mathematics");
    books[last].book_prize = 6798;
    books[last].lendingPrize_week = 28;
    books[last].rack_no = 1;
    books[last].category = 4;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "K. F Riley");
    strcpy(books[last].book_name, "Mathematical Methods For Physics And Engineering");
    books[last].book_prize = 1195;
    books[last].lendingPrize_week = 20;
    books[last].rack_no = 2;
    books[last].category = 4;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "William T Thomson");
    strcpy(books[last].book_name, "Introduction to Space Dynamics");
    books[last].book_prize = 1349;
    books[last].lendingPrize_week = 17;
    books[last].rack_no = 1;
    books[last].category = 5;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "Stephen Hawking");
    strcpy(books[last].book_name, "Brief Answers to the Big Questions");
    books[last].book_prize = 650;
    books[last].lendingPrize_week = 6;
    books[last].rack_no = 1;
    books[last].category = 5;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "Chris Hadfield");
    strcpy(books[last].book_name, "Earth");
    books[last].book_prize = 1094;
    books[last].lendingPrize_week = 9;
    books[last].rack_no = 2;
    books[last].category = 5;
    category[books[last].category][last]=true;
    last++;
    
    strcpy(books[last].author_name, "priyadarshi");
    strcpy(books[last].book_name, "Na savu nenu sastha nekendhuku");
    books[last].book_prize = 70000;
    books[last].lendingPrize_week = 70;
    books[last].rack_no = 1;
    books[last].category = 0;
    category[books[last].category][last]=true;
    last++;
}

bool strbkcmp(char* str1, char* str2){// to compare strings even if it is capital or small case char
    if (strlen(str1)==strlen(str2)) {
        int n=0;
        for (int i=0; i<strlen(str1); i++) {
            if (str1[i]==str2[i]||str1[i]==str2[i]+32||str1[i]==str2[i]-32) {
                n++;
            }
        }
        if (n==strlen(str1)){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

void print_book_details(int x){
    printf("-> Title of book: %s\n", books[x].book_name);
    printf("-> Author of book: %s\n", books[x].author_name);
    printf("-> Quantity: %d\n", books[x].quantity);
    printf("-> Categeory of book is: %s\n", cat_name[books[x].category]);
    printf("-> Book is in rack no: %d\n", books[x].rack_no);
    printf("-> Prize of book: %ld\n", books[x].book_prize);
    printf("-> Lending cost of book per week: %d\n", books[x].lendingPrize_week);
}

void search_Bname(void){
    char bn[50], c;
    printf("Enter book name: ");
    int i=0;
    c=getchar();
    /*
     dk why but first element is taken as '\n' in these functions, found by debugging.
     So to make code run first element is not collected
    */
    while ((c=getchar())!='\n') {
        bn[i++]=c;
    }
    bn[i]='\0';
    int count=0;
    for (int i=0; i<last; i++) {
        if (strbkcmp(books[i].book_name, bn)==1) {
            count++;
        }
    }
    if (count==0){
        printf("No book found with that name is found in library!!\n");
        printf("Redirected back to seaching methods...\n");
    }
    else{
        printf("\n%d books found with similar name..\n", count);
        int arr[count];
        count=0;
        for (int i=0; i<last; i++) {
            if (strbkcmp(books[i].book_name, bn)==1) {
                arr[count]=i;
                count++;
                printf("\n");
                printf("%d)\n", count);
                print_book_details(i);
                printf("\n");
            }
        }
        int target_book_index;
        int opt;
        printf("-> Enter 1 to puchase or lend a book from these books\n");
        printf("-> Enter 2 to go back to seaching methods\n");
        printf("Enter you option: ");
        scanf("%d", &opt);
        if (opt==1) {
            printf("* Enter index of book to puchase or lend as displayed above: ");
            scanf("%d", &target_book_index);
            target_book_index--;
            books[arr[target_book_index]].quantity--;
            printf("Information sucesfully updated......\n\n");
            printf("Please collect the book according to the below details: \n");
            print_book_details(arr[target_book_index]);
            printf("\n\nRedirected back to seaching methods...\n\n");
        }
        else{
            printf("\nRedirected back to seaching methods...\n");
        }
    }
}

void search_Bid(void){
    int bid;
    printf("Enter Book id: ");
    scanf("%d", &bid);
    int i;
    for (i=0; i<last; i++) {
        if (books[i].book_id == bid) {
            printf("book found!!\n book name: %s\n", books[i].book_name);
            break;
        }
    }
    int opt;
    printf("-> Enter 1 to puchase or lend a book from these books\n");
    printf("-> Enter 2 to go back to seaching methods\n");
    printf("Enter you option: ");
    scanf("%d", &opt);
    if (opt==1) {
        books[i].quantity--;
        printf("\nInformation sucesfully updated......\n\n");
        printf("Please collect the book according to the below details: \n");
        print_book_details(i);
        printf("\n\nRedirected back to seaching methods...\n\n");
    }
    else{
        printf("\nRedirected back to seaching methods...\n\n");
    }
}
void search_Bcat(void){
    int cat_opt;
    for(int i=0; i<=5; i++){
        printf("Enter %d for %s catagory\n", i+1, cat_name[i]);
    }
    printf("Enter category index: ");
    scanf("%d", &cat_opt);
    int count=0;
    for (int i=0; i<N; i++){
        if (category[cat_opt-1][i]) {
            count++;
        }
    }
    if (count==0) {
        printf("\nNo book found under this categeory!!\n");
        printf("Redirected back to seaching methods...\n\n");
        
    }
    else{
        printf("\nThere are %d books under this categeory...\n\n", count+1);
        int arr[count];
        count=0;
        for (int i=0; i<N; i++){
            if (category[cat_opt-1][i]) {
                arr[count]=i;
                count++;
                printf("%d)\n", count);
                print_book_details(i);
                printf("\n");
            }
        }
        int target_book_index;
        int opt;
        printf("-> Enter 1 to puchase or lend a book from these books\n");
        printf("-> Enter 2 to go back to seaching methods\n");
        printf("Enter you option: ");
        scanf("%d", &opt);
        if (opt==1) {
            printf("* Enter index of book to puchase or lend as displayed above: ");
            scanf("%d", &target_book_index);
            target_book_index--;
            books[arr[target_book_index]].quantity--;
            printf("Information sucesfully updated......\n\n");
            printf("Please collect the book according to the below details: \n");
            print_book_details(arr[target_book_index]);
            printf("\n\nRedirected back to seaching methods...\n\n");
        }
        else{
            printf("\nRedirected back to seaching methods...\n");
        }
    }
}

void search_Aname(void){
    char an[30], c;
    printf("Enter Author name: ");
    int i=0;
    c=getchar();
    /*
     dk why but first element is taken as '\n' in these functions, found by debugging.
     So to make code run first element is not collected
    */
    while ((c=getchar())!='\n') {
        an[i++]=c;
    }
    an[i]='\0';
    int count=0;
    for (int i=0; i<last; i++) {
        if (strbkcmp(books[i].author_name, an)==1) {
            count++;
        }
    }
    if (count==0){
        printf("No book found with that Author name is found in library!!\n");
        printf("Redirected back to seaching methods...\n");
    }
    else{
        printf("\n%d books of entered Author are found..\n", count);
        int arr[count];
        count=0;
        for (int i=0; i<last; i++) {
            if (strbkcmp(books[i].author_name, an)==1) {
                arr[count]=i;
                count++;
                printf("\n");
                printf("%d)\n", count);
                print_book_details(i);
                printf("\n");
            }
        }
        int target_book_index;
        int opt;
        printf("-> Enter 1 to puchase or lend a book from these books\n");
        printf("-> Enter 2 to go back to seaching methods\n");
        printf("Enter you option: ");
        scanf("%d", &opt);
        if (opt==1) {
            printf("* Enter index of book to puchase or lend as displayed above: ");
            scanf("%d", &target_book_index);
            target_book_index--;
            books[arr[target_book_index]].quantity--;
            printf("Information sucesfully updated......\n\n");
            printf("Please collect the book according to the below details: \n");
            print_book_details(arr[target_book_index]);
            printf("\n\nRedirected back to seaching methods...\n\n");
        }
        else{
            printf("\nRedirected back to seaching methods...\n\n");
        }
    }
}

void add_book(void){
    if (last>N) {
        printf("Cant add books library is full !!!");
    }
    else{
        printf("Enter title of book: ");
        scanf("%s", books[last].book_name);
        printf("Enter authoer name: ");
        char c;
        int i=0;
        c=getchar();
        /*
         dk why but first element is taken as '\n' in these functions, found by debugging.
         So to make code run first element is not collected
        */
        while ((c=getchar())!='\n') {
            books[last].author_name[i++]=c;
        }
        books[last].author_name[i]='\0';
        printf("Enter rack no: ");
        scanf("%d", &books[last].rack_no);
        printf("\n");
        for(int i=0; i<=5; i++){
            printf("Enter %d for %s catagory\n", i+1, cat_name[i]);
        }
        printf("Enter category: ");
        scanf("%d", &books[last].category);
        printf("Enter MRP of book (in rupees): ");
        scanf("%ld", &books[last].book_prize);
        printf("Enter lending cost per week (in rupees): ");
        scanf("%d", &books[last].lendingPrize_week);
        printf("Enter quantity: ");
        scanf("%d", &books[last].quantity);
        printf("Book has been sucessfully added to library!!!\n");
        printf("/nAloocated book id for this book is: %d\n", books[last].book_id);
        last++;
    }
}
void incrdec_qty_book(void){
    int bid;
    int q=0;
    bool id_found=false;
    printf("Enter book id to increase or decrease quantity: ");
    scanf("%d", &bid);
    for (int i=0; i<last; i++) {
        if (bid==books[i].book_id) {
            id_found=true;
            int opt;
            printf("Quantity of this book at present is: %d\n", books[i].quantity);
            printf("Enter 1 to increase quantity\n");
            printf("Enter 2 to decrease quantity\n");
            printf("Enter 3 for going back to MAIN MENU");
            scanf("%d", &opt);
            q=0;
            switch (opt) {
                case 1:
                    printf("Enter quantity of book to add: ");
                    scanf("%d",&q);
                    books[i].quantity+=q;
                    printf("\nRedirected back to MAIN MENU....\n\n");
                    break;
                case 2:
                    printf("Enter quantity of book to remove: ");
                    scanf("%d",&q);
                    if (q>books[i].quantity) {
                        books[i].quantity=0;
                    }
                    else{
                        books[i].quantity-=q;
                    }
                    printf("\nRedirected back to MAIN MENU....\n\n");

                    break;
                    
                default:
                    printf("\nRedirected back to MAIN MENU....\n\n");
                    break;
            }
            break;
        }
    }
    if (id_found==false) {
        printf("\nEntered book id is incorrect\n\nRedirecting to MAIN MENU....\n");
    }
}
int total_quantity(void){
    int tot_q=0;
    for (int i=0; i<last; i++) {
        tot_q+=books[i].quantity;
    }
    printf("There are a total of %d books (including copies) in library\n", tot_q);
    return tot_q;
}
void print_bookNameId(void){
    printf("\n");
    printf("Book names with ther id's: ");
    printf("(Book Name -> Book id)\n");
    for (int i=0; i<last; i++) {
        printf("%d) ", i+1);
        printf("%s->\t", books[i].book_name);
        printf("%d\n", books[i].book_id);
    }
}
void rmvbook_id(void){
    int bid;
    printf("Enter the book id of removing book: ");
    scanf("%d", &bid);
    bool id_found = false;
    for (int i=0; i<last; i++) {
        if (bid==books[i].book_id) {
            id_found=true;
            int temp=books[i].book_id;
            for (int j=i; j<last-1; j++) {
                books[j]=books[j+1];
            }
            books[last-1].book_id=temp;
            last--;
            printf("Book has been sucessfully deleted!!\n");
            break;
        }
    }
    if (id_found==false) {
        printf("\nEntered book id is incorrect\n\nRedirecting to MAIN MENU....\n");
    }
}
