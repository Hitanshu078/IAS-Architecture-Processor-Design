#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1000
#define SIZE_PC 10
#define BUFFER 500
//Instruction format 

typedef struct instruction
{
  long long int lhs;
  long long int rhs;
  long long int data;
} instruction;

//Registers

unsigned long long int MainMemory[MAX_SIZE];
long long int PC[SIZE_PC];
long long int MAR;
long long int IR;
long long int IBR;
instruction MBR;
long long int ACC;
long long int MQ;
long long int PC_index = 0;
long long int left_flag = 0; //If we have a single instruction _> by default its right instruction so 0
void PrintStatus_Instruction();
void PrintStatus_Exectuion();
void fetch(int value_at_pc);
void decode_execute(int IR, int MAR);
long long int lhsinst,rhsinst,leftmem,rightmem;

int Fact(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n *Fact(n - 1);
    }
}

void fetch(int value_at_pc)
{
    MAR = value_at_pc;
    MBR.lhs = MainMemory[MAR] >> 20; //data_
    if(MBR.lhs!=0)
        left_flag=1;
    MBR.rhs = MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
   
    if (left_flag == 0)
    {
        IR = (MBR.rhs) >> 12;
        MAR = ((MBR.rhs)) & 0b00000000111111111111;
        PrintStatus_Exectuion();
        decode_execute(IR, MAR);
        //decode on right
    }
    else
    {
        IBR = MBR.rhs;
        IR = (MBR.lhs) >> 12;
        MAR = ((MBR.lhs)) & 0b00000000111111111111;
        decode_execute(IR,MAR);
        IR = (IBR) >> 12;
        MAR=(IBR) & 0b00000000111111111111;
        decode_execute(IR,MAR);

        //decode left
        //decode right
    }
    PC_index++;
}

void decode_execute(int IR, int MAR)
{
    switch (IR) //Takes opcode
    {
        //MEMORY BASED
    case 0b00001010:
        printf("Detected LoadMQ\n");
        ACC = MQ;
        printf("Transfer of MQ to ACC Done.\n"); //Load MQ
        PrintStatus_Instruction();
        break;
    case 0b00001001:
        MBR.data = MainMemory[MAR];
        MQ = MBR.data;
        //load MQ M(X)
        PrintStatus_Instruction();
        break;
    case 0b00100001: //Stor M(X)
        printf("Detected STOR M(X)\n");
        MainMemory[MAR] = ACC;
        printf("Stored Succesfully\n");
        PrintStatus_Instruction();
        break;
    case 0b00000001: //Load M(X)
        printf("Detected LOAD M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC = MBR.data;
        printf("Load successful\n");
        PrintStatus_Instruction();
        break;

    case 0b00000010:
        printf("Detected -LOAD M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC = -MBR.data;
        printf("Load successful\n");
        PrintStatus_Instruction();
        break;
    case 0b00000100:
        printf("Detected LOAD -| M(X)|\n");
        MBR.data = -(long long int)fabs(MainMemory[MAR]);
        ACC = MBR.data;
        printf("Load successful\n");
        PrintStatus_Instruction();
        break;
    case 0b00000011:
        printf("Detected LOAD |M(X)|\n");
        MBR.data = MainMemory[MAR];
        ACC = (long long int)fabs(MBR.data);
        printf("Load successful\n");
        PrintStatus_Instruction();
        break;

        //JUMP BASED

    case 0b00001101:
        printf("JUMP to LHS M(X)\n");
        left_flag = 1;
        PC_index = MAR;
        PrintStatus_Instruction();
        break;
    case 0b00001110:
        printf("JUMP to RHS M(X)\n");
        left_flag = 0;
        PC_index = MAR;
        PrintStatus_Instruction();
        break;

    case 0b000011111:
        printf("JUMP TO LHS M(X) if AC is non-negative\n");
        if (ACC > 0)
        {
            left_flag = 1;
            PC[PC_index] = MainMemory[MAR];
        }
        PrintStatus_Instruction();
        break;
    case 0b00010000:
        printf("JUMP to RHS M(X) if AC is non-negative\n");
        if (ACC > 0)
        {
            left_flag = 0;
            PC[PC_index] = MainMemory[MAR];
        }
        PrintStatus_Instruction();
        break;

        //MODIFIED STOR

    case 0b00000101:
        printf("Detected add M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC += MBR.data;
        printf("Added to AC succesfully\n");
        PrintStatus_Instruction();
        break;
    case 0b00000111:
        printf("Detected add |M(X)|\n");
        MBR.data = (long long int)fabs(MainMemory[MAR]);
        ACC += MBR.data;
        printf("Added to AC succesfully\n");
        PrintStatus_Instruction();
        break;
    case 0b00000110:
        printf("Detected sub M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC -= MBR.data;
        printf("Subtracted from AC succesfully\n");
        PrintStatus_Instruction();
        break;
    case 0b00001000:
        printf("Detected sub |M(X)|\n");
        MBR.data = (long long int)fabs(MainMemory[MAR]);
        ACC -= MBR.data;
        printf("Subtracted from AC succesfully\n");
        PrintStatus_Instruction();
        break;
    case 0b00010100:
        printf("Detected Left Shift\n");
        ACC = ACC << 1;
        printf("Left shift successful\n");
        PrintStatus_Instruction();
        break;
    case 0b00010101:
        printf("Detected Right Shift\n");
        ACC = ACC >> 1;
        printf("Right shift successful\n");
        PrintStatus_Instruction();
        break;
    case 0b00001011:
        printf("Detected MUL M(x)\n");
        MBR.data = MainMemory[MAR];
        MQ = MQ * MBR.data;
        //MQ = (MQ * MBR.data) & 0b111111111111111111111111111111111111111111111111;
        //ACC = (ACC * MBR.data) >> 40;
        printf("Multiplication succesful\n");
        PrintStatus_Instruction();
        break;
    case 0b00001100:
        printf("Detected DIV M(X)\n");
        MBR.data = MainMemory[MAR];
        MQ = ACC / MBR.data;
        ACC = ACC % MBR.data;
        printf("Division successful \n");
        PrintStatus_Instruction();
        break;
    case 0b10111011: //NEW FACTORIAL CALCULATING FUNCTION
        printf("Detected FACT M(x)\n");
        MBR.data = MainMemory[MAR];
    
        // Initialize ACC to 1 for factorial computation
        ACC = 1;

        // Perform factorial computation in a loop
        while (MBR.data >= 1) {
            ACC *= MBR.data;
            MBR.data--;
        }

        printf("Fact Successful\n");
        PrintStatus_Instruction();
        break;
    case 0b11111111: //NEW COMPARE INSTRUCTION
        MBR.data = MainMemory[MAR];
        if(ACC < MBR.data)
        {
            printf("Invalid input(your n must be greater than r).\n");
            PC_index+=5;
        }
        else
        {
            printf("Valid Input\n");
        }
        break;
    }
}
void PrintStatus_Instruction()
{
    printf("PC = %lld\nIR = %lld\nMAR = %lld\nIBR = %lld\nMBR = %lld\nLeft Instruction = %lld\nRight Instruction = %lld\n\n", PC_index, IR, MAR, IBR, MBR.data, MBR.lhs, MBR.rhs);
}
void PrintStatus_Exectuion()
{
    printf("ACC = %lld\n MQ= %lld\n Value obtained from memory = %lld \n MBR = %lld\n\n ", ACC, MQ, MainMemory[MAR], MBR.data);
}
void permutate(int n,int r)
{

    MainMemory[100] = n;
    MainMemory[101] = r;

    //LOAD M(100) and CMP M(100)
    MainMemory[0] = 0b0000000100000110010011111111000001100101;

    //SUB M(101) and STOR M(101)
    MainMemory[1] = 0b0000011000000110010100100001000001100101;

    //FACT M(101) and STOR M(101)
    MainMemory[2] = 0b1011101100000110010100100001000001100101;

    //FACT M(100) and DIV M(101)
    MainMemory[3] = 0b1011101100000110010000001100000001100101;

    //Initialising program stack
    PC[0]=0;
    PC[1]=1;
    PC[2]=2;
    PC[3]=3;

    //First two instructions
    for (PC_index = 0; PC_index < 4;)
        fetch(PC[PC_index]);
    if(PC_index < 5)
    {
        printf("\nPermutations = %lli\n", MQ);
    }
}
int main()
{
    printf("Welcome to our IAS machine\nInput 1 to compute no of permutations of a number.\nInput 2 to switch off the machine.\nThis program displays values in registers and instructions running during each step.\n");
    int choice=0;
    int a,b;
    do
    {
        printf("\nEnter your choice\n");
        scanf("%i",&choice);
        switch(choice)
        {
            case 1:
                int n,r;
                printf("Enter the values of n and r\n");
                scanf("%d %d",&n,&r);
                permutate(n,r);  
                break;
            case 2:
                printf("Switching off machine.\n");
                break;
            default:
                printf("Invalid input.\n");
                break;
        }
    }
    while(choice!=2);
}