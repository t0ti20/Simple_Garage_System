#include <stdio.h>
#define Maximum_Clents 16
#define Maximum_Slots 4
#define Index_Not_Found -1
#define Second_Cost 0.000001
typedef int ID_t;
typedef enum Error_t
{
    Error_Ok,
    Error_Garage_IDs_Full,
    Error_Garage_Slots_Full,
    Error_ID_Not_Found,
    Error_Slot_Reserved,
    Error_Slot_Not_Found,
}Error_t;
typedef struct Time_t
{
    unsigned char Hours;
    unsigned char Minutes;
    unsigned char Seconds;
}Time_t;
typedef struct Slot_t
{
    Time_t Start_Time;
    ID_t ID_Number;
}Slot_t;
typedef struct Garage_t
{
    ID_t Clent_IDs[Maximum_Clents];
    Slot_t Garage_Slots[Maximum_Slots];
    unsigned char Reserved_Slots;
}Garage_t;

Garage_t DataBase;
Time_t Current_Time;

Error_t Add_ID(ID_t ID_Number)
{
    Error_t State=Error_Garage_IDs_Full;
    for(unsigned char Counter=0;Counter<Maximum_Clents;Counter++)
    {
        if(DataBase.Clent_IDs[Counter]){}
        else
        {
            DataBase.Clent_IDs[Counter]=ID_Number;
            State=Error_Ok;
            break;
        }
    }
    return State;
}
void Update_Time(void)
{
    Current_Time.Hours=11;
    Current_Time.Minutes=11;
    Current_Time.Seconds=11;
}
static char Get_Slot(ID_t ID_Number)
{
     char Index=Index_Not_Found;
     for(unsigned char Counter=0;Counter<Maximum_Slots;Counter++)
     {
          if(DataBase.Garage_Slots[Counter].ID_Number==ID_Number)
          {
               Index=Counter;
               break;
          }
          else{}
     }
     return Index;
}
static char Check_ID(ID_t ID_Number)
{
     char Index=Index_Not_Found;
     for(unsigned char Counter=0;Counter<Maximum_Clents;Counter++)
     {
          if(DataBase.Clent_IDs[Counter]==ID_Number)
          {
               Index=Counter;
               break;
          }
          else{}
     }
     return Index;
}
static Error_t Reserve_Slot(ID_t ID_Number)
{
     char Index = Check_ID(ID_Number);
     Error_t State = Error_Garage_Slots_Full;
     unsigned char Counter;
     if(Index==Index_Not_Found)State=Error_ID_Not_Found;
     else if(DataBase.Reserved_Slots>=Maximum_Slots)
     {
         State = Error_Garage_Slots_Full;
     }
     else
     {
          for(Counter=0;Counter<Maximum_Slots;Counter++)
          {
               if(DataBase.Garage_Slots[Counter].ID_Number==0)
               {
                    Update_Time();
                    DataBase.Garage_Slots[Counter].ID_Number = ID_Number;
                    DataBase.Garage_Slots[DataBase.Reserved_Slots].Start_Time = Current_Time;
                    DataBase.Reserved_Slots++;
                    State = Error_Ok;
                    break;
               }
               else {}
          }
     }
     return State;
}
static Error_t Free_Slot(ID_t ID_Number)
{
     Error_t State = Error_ID_Not_Found;
     unsigned char Counter;
     for(Counter=0;Counter<Maximum_Slots;Counter++)
     {
          if(DataBase.Garage_Slots[Counter].ID_Number==ID_Number)
          {
               DataBase.Garage_Slots[Counter].ID_Number=0;
               DataBase.Reserved_Slots--;
               State = Error_Ok;
               break;
          }
          else {}
     }
     return State;
}
Error_t Exit_Enter_Garage(ID_t ID_Number)
{
    Error_t State = Error_Ok;
    char Index=Check_ID(ID_Number);
    if(Index==Index_Not_Found)
    {
        State=Error_ID_Not_Found;
    }
    else
    {
        Index=Get_Slot(ID_Number);
        if(Index==Index_Not_Found)/*Enter Garage*/
        {
            State=Reserve_Slot(ID_Number);
        }
        else
        {/*Exit Garage*/
            State=Free_Slot(ID_Number);
        }
    }
    return State;
}

void print_slots_data() 
{
    printf("Reserved Slots Data:\n");
    for (unsigned char Counter = 0; Counter < Maximum_Slots; Counter++) {
        if (DataBase.Garage_Slots[Counter].ID_Number != 0) {
            printf("Slot %hhu - ID: %hhu, Start Time: %02d:%02d:%02d\n", Counter + 1,
                   DataBase.Garage_Slots[Counter].ID_Number, 
                   DataBase.Garage_Slots[Counter].Start_Time.Hours,
                   DataBase.Garage_Slots[Counter].Start_Time.Minutes,
                   DataBase.Garage_Slots[Counter].Start_Time.Seconds);
        }
    }
}

void Garage_Initialization(void)
{

     for(unsigned char Counter=0;Counter<Maximum_Clents;Counter++)DataBase.Clent_IDs[Counter]=0;
     for(unsigned char Counter=0;Counter<Maximum_Slots;Counter++)
     {
          DataBase.Garage_Slots[Counter].ID_Number=0;
          DataBase.Garage_Slots[Counter].Start_Time.Hours=0;
          DataBase.Garage_Slots[Counter].Start_Time.Minutes=0;
          DataBase.Garage_Slots[Counter].Start_Time.Seconds=0;
     }
     DataBase.Reserved_Slots=0;
    Add_ID(11);
    Add_ID(22);
}
char Calculate_Cost(Slot_t Slot_Data)
{
    char Cost=Index_Not_Found;
    Update_Time();
    Cost=(char)((((Current_Time.Hours-Slot_Data.Start_Time.Hours)*60.0*60.0)+((Current_Time.Minutes-Slot_Data.Start_Time.Minutes)*60.0)+((Current_Time.Seconds-Slot_Data.Start_Time.Seconds)))*((double)Second_Cost));
    return Cost;
}
int main() {
    Garage_Initialization();
    int choice;
    while (1) {
        printf("--------------------------------\n");
        print_slots_data();
        printf("--------------------------------");
        printf("\nMenu:\n");
        printf("1. Add ID\n");
        printf("2. Enter/Exit Garage\n");
        printf("3. Print Slots Data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                ID_t id;
                printf("Enter the ID to add: ");
                scanf("%hhu", &id);
                Error_t result = Add_ID(id);
                if (result == Error_Ok) {
                    printf("ID %hhu added successfully.\n", id);
                } else {
                    printf("Error: Garage is full.\n");
                }
                break;
            }
            case 2: {
                ID_t id;
                printf("Enter the ID to enter/exit the garage: ");
                scanf("%hhu", &id);
                Error_t result = Exit_Enter_Garage(id);
                if (result == Error_Ok) {
                    printf("Operation successful for ID %hhu.\n", id);
                } else if (result == Error_Garage_Slots_Full) {
                    printf("Error: All slots are reserved.\n");
                } else if (result == Error_ID_Not_Found) {
                    printf("Error: ID %hhu not found in the database.\n", id);
                } else if (result == Error_Slot_Reserved) {
                    printf("Error: Slot already reserved for ID %hhu.\n", id);
                } else if (result == Error_Slot_Not_Found) {
                    printf("Error: Slot not found for ID %hhu.\n", id);
                }
                break;
            }
            case 3: {
                print_slots_data();
                break;
            }
            case 4:  // Exit the program
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
