
/*********
This is an E-Shopping Website created using C .
Creaters - 1) Jay Puri Goswami
           2) Harshal Sable


IMP - The database of the product has to entered manually . The size of the database can be specifies in int main

Index -
1) Int -main - Line number 692
2) Structure of the product detail - Line number 43
3) Structure of the dealer detail - Line number 57
4) Structure of the account  holder/purchaser  - Line number 79
5) Initialize function(Which initialize the product detail 0 - Line number 111
6) Search function(Which searches according to the criteria of search given by the user - Line number 156
7) Create account (It creates an account for a new user 0 - line number 415
8) account already there (While creating account, this utility function checks whether the given user is already registered or not) -Line number 444
9) Show account detail ( This function checks the details of the account_holder , including the  -  Line number 464
                        name & all personalized details & purchase history also )

10) Sign in (This function helps in the signing-in of the user) - Line number 488
(This is requires when the purchaser need to buy a product)

11) Show product detail (This function shows all the detail of a given product entered by the user)  -Line 511

12) Recommend (This function helps in recommending the products to the user , after th user buys somep product) - Line number  546
13) Recommend from the same (This function helps in recommending product to the user from the same brans ) - Line number 526

14) Buy product(This function helps in buying the product from the available products in the stock) - Line number 573

15) Re-order(This function helps in the re-ordering of a specific product from the usert history on the request of user ) -Line number 651

*********/







#include<stdio.h>
#include<string.h>


struct prod_det                 //details of the products available
{
    char brand_name[100] ;
    int id ;
    char prod_name[100] ;
    float price ;
    char color[20];
    int stock;
    char dealer[50];
    int offer ;
    char category[100] ;

} ;

struct dealer_detail                //details of the dealer
{
    char name[50] ;
    float rating ;
    struct pd
    {
        char prod_namea[100] ;
        int no_sold = 0 ;
        int item_have = 0 ;
    };

    struct pd prod_detail ;

}   ;
struct dealer_detail dealer[10] ; int deal_counter =  0  , total_ratings[10] = {0};
/*
    dealer is the array to the struct dealer_detail .
    deal_counter counts the number of entries into the dealer
    total_ratings[i] counts the number of ratings given to the ith dealer
*/


struct account                            //details of the purchaser or  user
{
    int id ;
    char name[100] ;
    char password[100] ;
    char address[500] ;
    char email[500] ;
    struct history                 // This struct inside the account stores the details of purchase history
    {
        char dealer[50] ;
        char product_name[100] ;
        int quantity ;
        float rating ;
        float price ;

    };

    struct history my_order[100] ;
};


struct account database[100] ;  int database_counter = 0 , my_order_index[100] = {0}  ;
/*
    database is the array to the struct account which holds the details of users
    data_base counter is a global variable which counts the number of users registered
    my_order_index is a global counter variable used to look for the proper storage of the product purchased in the history struct of account

*/




void initialize(struct prod_det prods[] ,  int sz)   //This is used to initialize the details & values of product
{
    for(int j = 0 ; j<sz ; j++)
    {
        printf("Enter brand name\t") ;scanf("%s",prods[j].brand_name) ; printf("\n") ;
        printf("Enter product id \t") ; scanf("%d",&prods[j].id) ; printf("\n") ;
        printf("Enter product name\t") ; scanf("%s",prods[j].prod_name); printf("\n") ;
        printf("Enter Price\t") ; scanf("%f",&prods[j].price); printf("\n") ;
        printf("Enter Color\t") ; scanf("%s",prods[j].color); printf("\n") ;
        printf("Enter Stock\t") ; scanf("%d",&prods[j].stock); printf("\n") ;
        printf("Enter dealer\t") ; scanf("%s",prods[j].dealer); printf("\n") ;

        int flag = 0 ;
        for(int k= 0 ; k<deal_counter && flag == 0  ; k++)
        {
            if(strcmp(dealer[k].name ,prods[j].dealer ) == 0)
            {
                flag = 1 ;
                strcpy(dealer[k].prod_detail.prod_namea  ,  prods[j].prod_name) ;
                dealer[k].prod_detail.item_have +=1 ;

            }
        }
        if(flag = 1)    // Means the dealer is new
        {
            strcpy(dealer[deal_counter].name,prods[j].dealer) ;
            strcpy(dealer[deal_counter].prod_detail.prod_namea ,prods[j].prod_name) ;
            dealer[deal_counter].prod_detail.item_have +=1 ;
            deal_counter+= 1 ;
        }

        printf("Enter offer\t") ; scanf("%d",&prods[j].offer); printf("\n") ;
        printf("Enter category\t") ; scanf("%s",prods[j].category); printf("\n") ;
    }
}



//This refers to Q.1 of the assignment
/*
This functions searches according to the criteria entered by user

This shows the product of given criteria having least price & the highest rated dealer
*/

void search_option(struct prod_det prods[] , int sz)
{
    printf("Choose search Criteria \n1) Category\n2)Product Name\n3)Color\n4)Brand name\n")  ;
    int option ;
    scanf("%d",&option) ;

    switch(option)
    {
        case(1):
        {
            printf("Enter search key\n") ;
            char key[50] ; scanf("%s",key) ;
            int price[sz] , idi[sz] , k = 0 ;
            //flag = 0 will signify that the key is found
            for(int j = 0 ; j<sz  ; j++)
            {
                if(strcmp(key,prods[j].category) == 0)
                {
                        price[k] = prods[j].price ; idi[k] = prods[j].id ; k+=1 ;
                }
            }
            if(k==0)
            {
                printf("The category you entered is not found\n") ;
            }
            else
            {
                int minium[k]  , min_id , mini_counter = 0   ,minimum = 32000;

                //My minium stores all the id where the minimum price occurs

                for(int j =  0 ; j<k;j++)
                {
                    if(price[j]<minimum)
                    {
                        minimum = price[j] ;
                    }
                }
                for(int j = 0 ; j<k ; j++)
                {
                    if(price[j] == minimum)
                    {
                        minium[mini_counter] = idi[j] ;  mini_counter+=1 ;
                    }
                }


                int max_sold = 0 , max_index_aa , prod_id_uu ;
                for(int j = 0 ; j<mini_counter ; j++)
                {
                    for(int rr = 0 ; rr<deal_counter ; rr++)
                    {
                        if(strcmp(prods[j].dealer , dealer[rr].name) == 0)
                        {
                            if(max_sold<dealer[rr].prod_detail.no_sold)
                            {
                                max_sold = dealer[rr].prod_detail.no_sold ; max_index_aa = rr ; prod_id_uu = j ;
                            }
                        }
                    }
                }

                printf("Dealer's name is %s\t and Category\n",dealer[max_index_aa] , prods[prod_id_uu].category) ;
            }
            break ;
        }
        case(2):
        {
             printf("Enter search key\n") ;
            char key[50] ; scanf("%s",key) ;
            int price[sz] , idi[sz] , k = 0 ;
            //flag = 0 will signify that the key is found
            for(int j = 0 ; j<sz  ; j++)
            {
                if(strcmp(key,prods[j].prod_name) == 0)
                {
                        price[k] = prods[j].price ; idi[k] = prods[j].id ; k+=1 ;
                }
            }
            if(k==0)
            {
                printf("The product name   you entered is not found\n") ;
            }
            else
            {
                int minium[k]  , min_id , mini_counter = 0   ,minimum = 32000;

                //My minium stores all the id where the minimum price occurs

                for(int j =  0 ; j<k;j++)
                {
                    if(price[j]<minimum)
                    {
                        minimum = price[j] ;
                    }
                }
                for(int j = 0 ; j<k ; j++)
                {
                    if(price[j] == minimum)
                    {
                        minium[mini_counter] = idi[j] ;  mini_counter+=1 ;
                    }
                }


                int max_sold = 0 , max_index_aa , prod_id_uu ;
                for(int j = 0 ; j<mini_counter ; j++)
                {
                    for(int rr = 0 ; rr<deal_counter ; rr++)
                    {
                        if(strcmp(prods[j].dealer , dealer[rr].name) == 0)
                        {
                            if(max_sold<dealer[rr].prod_detail.no_sold)
                            {
                                max_sold = dealer[rr].prod_detail.no_sold ; max_index_aa = rr ; prod_id_uu = j ;
                            }
                        }
                    }
                }

                printf("Dealer's name is %s\t and the product name\n",dealer[max_index_aa] , prods[prod_id_uu].prod_name) ;

            }
            break ;
        }
        case(3):
        {
            printf("Enter search key\n") ;
            char key[50] ; scanf("%s",key) ;
            int price[sz] , idi[sz] , k = 0 ;
            //flag = 0 will signify that the key is found
            for(int j = 0 ; j<sz  ; j++)
            {
                if(strcmp(key,prods[j].color) == 0)
                {
                        price[k] = prods[j].price ; idi[k] = prods[j].id ; k+=1 ;
                }
            }
            if(k==0)
            {
                printf("The color you entered is not found\n") ;
            }
            else
            {
                int minium[k]  , min_id , mini_counter = 0   ,minimum = 32000;

                //My minium stores all the id where the minimum price occurs

                for(int j =  0 ; j<k;j++)
                {
                    if(price[j]<minimum)
                    {
                        minimum = price[j] ;
                    }
                }
                for(int j = 0 ; j<k ; j++)
                {
                    if(price[j] == minimum)
                    {
                        minium[mini_counter] = idi[j] ;  mini_counter+=1 ;
                    }
                }


                int max_sold = 0 , max_index_aa , prod_id_uu ;
                for(int j = 0 ; j<mini_counter ; j++)
                {
                    for(int rr = 0 ; rr<deal_counter ; rr++)
                    {
                        if(strcmp(prods[j].dealer , dealer[rr].name) == 0)
                        {
                            if(max_sold<dealer[rr].prod_detail.no_sold)
                            {
                                max_sold = dealer[rr].prod_detail.no_sold ; max_index_aa = rr ; prod_id_uu = j ;
                            }
                        }
                    }
                }

                printf("Dealer's name is %s\t and the Color\n",dealer[max_index_aa] , prods[prod_id_uu].color) ;
            }
            break ;
        }
        case(4):
        {
             printf("Enter search key\n") ;
            char key[50] ; scanf("%s",key) ;
            int price[sz] , idi[sz] , k = 0 ;
            //flag = 0 will signify that the key is found
            for(int j = 0 ; j<sz  ; j++)
            {
                if(strcmp(key,prods[j].brand_name) == 0)
                {
                        price[k] = prods[j].price ; idi[k] = prods[j].id ; k+=1 ;
                }
            }
            if(k==0)
            {
                printf("The Brand name you entered is not found\n") ;
            }
            else
            {
              int minium[k]  , min_id , mini_counter = 0   ,minimum = 32000;

                //My minium stores all the id where the minimum price occurs

                for(int j =  0 ; j<k;j++)
                {
                    if(price[j]<minimum)
                    {
                        minimum = price[j] ;
                    }
                }
                for(int j = 0 ; j<k ; j++)
                {
                    if(price[j] == minimum)
                    {
                        minium[mini_counter] = idi[j] ;  mini_counter+=1 ;
                    }
                }


                int max_sold = 0 , max_index_aa , prod_id_uu ;
                for(int j = 0 ; j<mini_counter ; j++)
                {
                    for(int rr = 0 ; rr<deal_counter ; rr++)
                    {
                        if(strcmp(prods[j].dealer , dealer[rr].name) == 0)
                        {
                            if(max_sold<dealer[rr].prod_detail.no_sold)
                            {
                                max_sold = dealer[rr].prod_detail.no_sold ; max_index_aa = rr ; prod_id_uu = j ;
                            }
                        }
                    }
                }

                printf("Dealer's name is %s\t and the brand name\n",dealer[max_index_aa] , prods[prod_id_uu].brand_name) ;
            }
            break ;
        }

        default :
        {
        printf("You entered wrong choice \n") ;
        search_option(prods,4) ;

        }

    }


}

int create_checker = 0 ;                      // If it is zero , means the details are new to the database

void is_already_there(char email[],int database_counter ,  struct account database[]) ;


void create_account()                         // This utility function creates the account for the user or purchaser
{
    printf("Enter your Email-Id\n")  ;  scanf("%s",database[database_counter].email) ;
    create_checker = 0 ;
    is_already_there(database[database_counter].email,database_counter,database) ;
    if(create_checker == 0)
    {
        printf("Enter name\t") ;
        scanf("%s",database[database_counter].name) ; printf("\n") ;
        printf("Create Password\t") ;
        scanf("%s",database[database_counter].password) ;  printf("\n") ;
        printf("Enter address\t") ;
        scanf("%s",database[database_counter].address) ; printf("\n") ;
        printf("Your id number is\t%d",database_counter+1) ; printf("\n") ;
        database[database_counter].id = database_counter+1 ;  database_counter+=1 ;
    }
    else if (create_checker == 1)
    {
        create_checker = 0 ;
    }

    return ;
}


/*
This utility function checks if the given primary key(i.e Email in this case) already exist in the database or not . If it exist , then they're asked
 to re-check their Email-Id
*/
void is_already_there(char email[],int database_counter ,  struct account database[])
{
    for(int j = 0 ; j<database_counter && create_checker == 0 ; j++)
    {
        if(strcmp(email,database[j].email) == 0)
        {
            printf("Email already exist\n") ; create_checker = 1  ;
        }

    }
    if(create_checker == 1)
    {
        create_account() ;
    }


}


// This function shows the details of your account
void show_account_detail()
{
    int id_number ;
    printf("Enter your id number\t") ;  scanf("%d",&id_number) ;  printf("\n") ;
    printf("Your Name is \t%s" , database[id_number-1].name) ; printf("\n") ;
    printf("Your password is \t%s" , database[id_number-1].password) ; printf("\n") ;
    printf("Your address is \t%s" , database[id_number-1].address) ; printf("\n") ;
    printf("Your order history is \n") ;
    for(int j = 0 ; j<my_order_index[id_number - 1] ; j++)
    {
        printf("Dealer name \t%s" , database[id_number-1].my_order[j].dealer) ;  printf("\n") ;
        printf("Product Name \t%s",database[id_number-1].my_order[j].product_name) ; printf("\n") ;
        printf("Quantity \t%d",database[id_number-1].my_order[j].quantity) ; printf("\n") ;
        printf("Rating given \t%d",database[id_number-1].my_order[j].rating) ; printf("\n") ;
        printf("Price \t%f",database[id_number-1].my_order[j].price) ;  printf("\n") ;

    }
    printf("\n") ;
}


/*
This functions helps you to sign-in/log-in , so that they can purchase products
*/
int sign_in(struct account database[], int sz)
{
    char email[500] , passw[100] ;  int id_return ; //This is the id We'll return through which we'll know the details of the purchaser
    printf("Enter your Email-Id\t") ; scanf("%s",email) ; printf("\n") ;
    printf("Enter password\t") ; scanf("%s" ,passw) ; int flag = 0 ;
    for(int j = 0 ; j<sz && flag == 0 ; j++)
    {
        if((strcmp(email,database[j].email) == 0) && strcmp(passw,database[j].password)==0)
        {
            id_return = j+1 ; flag = 1 ;
        }
   }
   if(flag == 0)
   {
       printf("You entered wrong email or password , please consider to sign in again\n") ;
       id_return = sign_in(database,sz) ;
   }

   return id_return ;

}


void show_all_product(struct prod_det prod[] , int sz)                     //This function shows the detail of all the products
{
    printf("All the available products are \n") ;
    printf("Product name\tID\tBrand Name\tPrice\tColor\tStock\tDealer\tOffer\tCategory\n") ;
    for(int j = 0 ; j<sz ; j++)
    {
        printf("%s\t%d\t%s\t%f\t%s\t%d\t%s\t%d\t%s",prod[j].prod_name ,prod[j].id,prod[j].brand_name,prod[j].price, prod[j].color,prod[j].stock ,
                prod[j].dealer , prod[j].offer , prod[j].category)  ; printf("\n") ;
    }
}

/*
This is in reference to question no. 2
It recommends the related products based on previous purchase using brand as the criteria
*/
void recommend_from_the_same(struct prod_det prod[] , char brand_name[] , int sz)
{
    int flag_not_used = 0 ;
    for(int uu = 0 ; uu<sz ; uu++)
    {

        if(strcmp(prod[uu].brand_name,brand_name) == 0)
        {
            if(flag_not_used == 0)
            {
                printf("Product name\tID\tBrand Name\tPrice\tColor\tStock\tDealer\tOffer\tCategory\n") ; flag_not_used  =1 ;
            }
            printf("%s\t%d\t%s\t%f\t%s\t%d\t%s\t%d\t%s",prod[uu].prod_name ,prod[uu].id,prod[uu].brand_name,prod[uu].price, prod[uu].color,
                   prod[uu].stock ,prod[uu].dealer , prod[uu].offer , prod[uu].category)  ;
        }
    }

}

//It recommends the related products using history as the criteria
void recommend(struct prod_det prod[], int sz ,struct account database[] , int database_counter)
{
    int flag_not_used = 0 ;
    for(int rre = 0 ; rre<database_counter ; rre++)
    {
        for(int eee = 0 ; eee<my_order_index[rre] ; eee++)
        {

            for(int zzz = 0 ; zzz<sz ; zzz++)
            {
                if(strcmp(prod[zzz].prod_name ,database[rre].my_order[eee].product_name) == 0)
                {
                    if(flag_not_used == 0)
                    {
                        printf("Product name\tID\tBrand Name\tPrice\tColor\tStock\tDealer\tOffer\tCategory\n") ; flag_not_used  =1 ;
                    }

                    printf("%s\t%d\t%s\t%f\t%s\t%d\t%s\t%d\t%s",prod[zzz].prod_name ,prod[zzz].id,prod[zzz].brand_name,prod[zzz].price
                    , prod[zzz].color,prod[zzz].stock ,prod[zzz].dealer , prod[zzz].offer , prod[zzz].category)  ;
                }
            }
        }
    }

}


void buy_product(struct prod_det prods[], int sz)   //This function helps in buying product from the database
{
    int user_id =  sign_in(database, database_counter)   ; int quantitya  ;
    int buy_id  ;
    show_all_product(prods , sz) ;
    printf("\n") ;
    printf("Enter the id of the product you want to buy \t") ; scanf("%d",&buy_id) ;  printf("\n") ;
    printf("Enter the quantity\t") ; scanf("%d",&quantitya) ;

    int index_of_prod , flag = 0 ;
    for(int j = 0 ; j<sz && flag == 0 ; j++)
    {
        if(prods[j].id == buy_id)
        {
            flag = 1 ; index_of_prod = j ;
        }
    }

    strcpy(database[user_id-1].my_order[my_order_index[user_id-1]].dealer, prods[index_of_prod].dealer) ;
    strcpy(database[user_id-1].my_order[my_order_index[user_id-1]].product_name ,prods[index_of_prod].prod_name) ;
    if(quantitya > prods[index_of_prod].stock)
    {
        while(quantitya >prods[index_of_prod].stock )
        {
            printf("We have only %d available in stock \n",prods[index_of_prod].stock) ;
            printf("If you want to reorder your quantity , enter the quantity or enter 0 for quitting") ;
            scanf("%d",&quantitya) ;
        }
        if(quantitya == 0)
        {
            return ;
        }
        database[user_id-1].my_order[my_order_index[user_id-1]].quantity = quantitya ;
        prods[index_of_prod].stock-=(quantitya) ;  int flagty = 0 ;
        for(int tyt = 0 ; tyt <deal_counter && flagty == 0 ; tyt++)
        {
            if(strcmp(prods[index_of_prod].dealer , dealer[tyt].name) == 0)
            {
                flagty = 1 ; dealer[tyt].prod_detail.item_have-=quantitya ; dealer[tyt].prod_detail.no_sold+=(quantitya) ;
            }
        }
    }
    else
    {
        database[user_id-1].my_order[my_order_index[user_id-1]].quantity = quantitya ;
        prods[index_of_prod].stock-=(quantitya) ;
    }

    database[user_id-1].my_order[my_order_index[user_id-1]].price = prods[index_of_prod].price*((100 - prods[index_of_prod].offer)/100) ;

    printf("Order done successfully \t") ;
    printf("How would you rate(out of 5) \n") ;  int flagqa = 0 ;
    scanf("%f" , &database[user_id-1].my_order[my_order_index[user_id-1]].rating) ;
    for(int j = 0 ; j<deal_counter && flagqa == 0 ; j++)
    {
        if(strcmp(dealer[j].name ,prods[index_of_prod].dealer) == 0)
        {
            dealer[j].rating*=(total_ratings[j]) ; dealer[j].rating+=(database[user_id-1].my_order[my_order_index[user_id-1]].rating) ; total_ratings[j]+=1 ;
            dealer[j].rating/=total_ratings[j] ;
            flagqa = 1 ;

        }
    }

    my_order_index[user_id-1]+=1 ;
    printf("Recommendation for you from the same brand \n") ;
    recommend_from_the_same(prods ,prods[index_of_prod].brand_name, sz) ;

    printf("\n Other recommendations are \n") ;
    recommend(prods,sz , database , database_counter) ;
}



/*
This function is in reference to Q.3
It helps in re-ordering the product from the history of your account
*/
void reorder(struct prod_det prod[], int sz ,struct account database[] , int database_counter )
{
    int id = sign_in(database, database_counter) ;
    printf("Your order history is \n") ;  int tyy = id ;
    printf("Id\tDealer\tProduct name\tQuantity\tRating\tPrice\n") ;
    for(int tty = 0 ; tty <my_order_index[tyy] ; tty++)
    {
        printf("%d\t%s\t%s\t%d\t%f\t%f\n" ,tty+1 ,database[tyy].my_order[tty].dealer ,database[tyy].my_order[tty].product_name ,
            database[tyy].my_order[tty]. quantity , database[tyy].my_order[tty].rating,database[tyy].my_order[tty].price  ) ;
    }

    int id_chosen ,  quantity ;
    printf("Choose among the following items (choose the id number ") ; scanf("%d",&id_chosen) ;
    id_chosen-=1 ; printf("Enter the required Quantity\n") ; scanf("%d",&quantity) ;   int flag_now_used = 0 ;
    for(int t = 0 ; t<sz ; t++ )
    {
        if(strcmp(prod[t].dealer ,database[id_chosen].my_order[id_chosen].dealer ) == 0
           && strcmp(prod[t].prod_name , database[id_chosen].my_order[id_chosen].product_name) == 0)

        {

            if(prod[t].stock < quantity)
            {
                if(flag_now_used == 0)
                {
                    printf("Product name\tID\tBrand Name\tPrice\tColor\tStock\tDealer\tOffer\tCategory\n") ; flag_now_used = 1 ;
                }
                int zzz = t ;

                printf("%s\t%d\t%s\t%f\t%s\t%d\t%s\t%d\t%s",prod[zzz].prod_name ,prod[zzz].id,prod[zzz].brand_name,prod[zzz].price
                    , prod[zzz].color,prod[zzz].stock ,prod[zzz].dealer , prod[zzz].offer , prod[zzz].category)  ;
            }

        }
    }



}


int main()
{
    struct prod_det prods[100] ;  int sz = 1 ;
    initialize(prods , sz) ;
    printf("Welcome to E-shopping\n") ;
    printf("Choose among the following commands to continue\n") ;
    printf("1)Search\n") ;
    printf("2)Sign-Up\n") ;
    printf("3)Sign-In\n") ;
    printf("4)Show account Details \n") ;
    printf("5) Show All product details\n") ;
    printf("6)Buy product\n") ;
    printf("7)Re-order\n") ;
    printf("8)Recommend\n") ;
    printf("Enter 0 for exit") ;
    int choice ; scanf("%d" , &choice) ; int flag_now_final = 0 ;
    while(flag_now_final == 0 )
    {
        switch(choice)
        {
            case(1) :
                {
                        search_option(prods ,sz) ;  break ;

                }
            case(2) :
                {
                        create_account() ; break ;
                }
            case(3) :
                {
                        sign_in(database, sz) ; break ;
                }
            case(4) :
                {
                        show_account_detail() ; break ;
                }
            case(5) :
                {
                        show_all_product(prods ,sz) ; break ;
                }
            case(6):
                {
                        buy_product(prods,sz) ; break ;
                }
            case(7):
                {
                        reorder(prods, sz ,database , database_counter) ; break ;
                }
            case(8):
                {
                       recommend(prods,sz ,database ,database_counter)   ;  break ;
                }

            default:
                {
                    flag_now_final = 1 ;
                }

        }
        printf("\nEnter choice again\t") ;
        scanf("%d",&choice) ;
        printf("\n") ;
    }

return 0 ;
}



/** End of the project **/
