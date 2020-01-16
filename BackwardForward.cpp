//
//  BackwardForward.cpp
//  Auto program
//
//  Created by Britain Mackenzie on 10/5/19.
//  Copyright © 2019 Britain Mackenzie. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

struct item{
    std::string name = "";
    int pos = 0;
    bool inst = false;
    bool value = false;
};

item vars[90];

int temp=-1;
int k, n, s, sn, qp;
char choice;
std::vector <int> statsk;

int backward();
int forward(int position);
int findVar(int sn, struct item *conclt[], struct item *clvarlt[]);
void instantiate(int, bool);
int solve(struct item *clvarlt[]);
bool checkChar();

int main(){
    //*******intiialization********
    
    //BC Conc vars
    //problems 1-21
    vars[1].name = "problem[BATDAMAGE]";
    vars[2].name = "problem[BATPROBLEM]";
    vars[3].name = "problem[ALTERNATOR]";
    vars[4].name = "problem[WIRES]";
    vars[5].name = "problem[STARTER]";
    vars[6].name = "problem[IGNITSWITCH]";
    vars[7].name = "problem[BELT]";
    vars[8].name = "problem[FUELPUMP]";
    vars[9].name = "problem[IGNITION]";
    vars[10].name= "problem[WARNLIGHT]";  
    vars[11].name= "problem[STEERING]";
    vars[12].name= "problem[TIREPRESSURE]";
    vars[13].name= "problem[TIREFLAT]";
    vars[14].name= "problem[SUSPENSION]";
    vars[15].name= "problem[REALIGN]";
    vars[16].name= "problem[TIEROD]";
    vars[17].name= "problem[BEARINGS]";
    vars[18].name= "problem[CHECKBRAKE]";
    vars[19].name= "problem[ACISSUE]";
    vars[20].name= "problem[BRAKEWEAR]";
    vars[21].name= "problem[OTHER]";
    
    //intermediate problems 22-30
    vars[22].name= "hardStart";
    vars[23].name= "batIssue";
    vars[24].name= "checkStarter";
    vars[25].name= "checkOther";
    vars[26].name= "handlingCheck";
    vars[27].name= "suspSysIssue";
    vars[28].name= "tireBrake";
    vars[29].name= "otherIssue";
    vars[30].name= "noiseCheck";
    //varlist
    vars[31].name= "start";
    vars[32].name= "engTurn";
    vars[33].name= "corroded";
    vars[34].name= "charge";
    vars[35].name= "wireDamage";
    vars[36].name= "starterWork";
    vars[37].name= "timingBelt";
    vars[38].name= "fuelPressure";
    vars[39].name= "engLight";
    vars[40].name= "handlingProb";
    vars[41].name= "turnHard";
    vars[42].name= "tireInflated";
    vars[43].name= "tireLeak";
    vars[44].name= "susWear";
    vars[45].name= "alignment";
    vars[46].name= "tieRodLoose";
    vars[47].name= "tireSpin";
    vars[48].name= "noise";
    vars[49].name= "airCool";
    vars[50].name= "highPitch";
    //FC vars
    //all other than BC
    vars[51].name= "keyGood";
    vars[52].name= "otherBat";
    vars[53].name= "batCharge";
    vars[54].name= "visualInspection";
    vars[55].name= "replicate";
    vars[56].name= "dangerous";
    vars[57].name= "fuelLineIssue";
    vars[58].name= "damage";
    vars[59].name= "looseBrake";
    vars[60].name= "whenStopping";
    //have[]
    vars[61].name= "have[BAT]";
    vars[62].name= "have[WIRES]";
    vars[63].name= "have[STARTER]";
    vars[64].name= "have[PUMP]";
    vars[65].name= "have[TIRE]";
    vars[66].name= "have[TIEROD]";
    vars[67].name= "have[BEARINGS]";
    vars[68].name= "have[REFRIGERANT]";
    vars[69].name= "have[BRAKE]";
    //replace[]
    vars[70].name= "replace[BATDAMAGE]";
    vars[71].name= "replace[BATPROB]";
    vars[72].name= "replace[ALTERNATOR]";
    vars[73].name= "replace[WIRES]";
    vars[74].name= "replace[STARTER]";
    vars[75].name= "replace[IGNITSWITCH]";
    vars[76].name= "replace[BELT]";
    vars[77].name= "replace[FUELPUMP]";
    vars[78].name= "replace[IGNITION]";
    vars[79].name= "replace[TIREFLAT]";
    vars[80].name= "replace[BRAKE]";
    vars[81].name= "replace[TIEROD]";
    //fix[]
    vars[82].name= "fix[STEERING]";
    vars[83].name= "fix[TIREPRESSURE]";
    vars[84].name= "fix[SUSPENSION]";
    vars[85].name= "fix[REALIGN]";
    vars[86].name= "fix[BEARINGS]";
    vars[87].name= "fix[BRAKE]";
    vars[88].name= "fix[ACISSUE]";
    vars[89].name= "warnLightInspection";
    
    
    //update position in array
    for(int i=1; i<87; i++){
        vars[i].pos=i;
    }
    
    forward(backward());
    
    return 0;
}

int backward(){
    int problem =0;
    
    struct item *conclt[31] = {NULL,    &vars[22], &vars[23], &vars[24], &vars[1],
                                        &vars[2],  &vars[3],  &vars[4],  &vars[5],
                                        &vars[6],  &vars[25], &vars[7],  &vars[8],
                                        &vars[9],  &vars[10], &vars[26], &vars[11],
                                        &vars[12], &vars[13], &vars[27], &vars[14],
                                        &vars[15], &vars[16], &vars[28], &vars[17],
                                        &vars[18], &vars[29], &vars[19], &vars[30],
                                        &vars[20], &vars[21]};
    
    struct item *varlt[21] = {NULL,     &vars[31], &vars[32], &vars[33], &vars[34],
                                        &vars[35], &vars[36], &vars[37], &vars[38],
                                        &vars[39], &vars[40], &vars[41], &vars[42],
                                        &vars[43], &vars[44], &vars[45], &vars[46],
                                        &vars[47], &vars[48], &vars[49], &vars[50]};
    
                                        //IF        &&         &&       &&
    struct item *clvarlt[121] = {NULL,  &vars[31],  NULL,     NULL,      NULL,      //1
                                        &vars[22], &vars[32], NULL,      NULL,      //5
                                        &vars[22], &vars[32], NULL,      NULL,      //9
                                        &vars[23], &vars[33], NULL,      NULL,      //13
                                        &vars[23], &vars[33], &vars[34], NULL,      //17
                                        &vars[23], &vars[33], &vars[34], &vars[35], //21
                                        &vars[23], &vars[33], &vars[34], &vars[35], //25
                                        &vars[24], &vars[36], NULL,      NULL,      //29
                                        &vars[24], &vars[36], NULL,      NULL,      //33
                                        &vars[22], &vars[32], NULL,      NULL,      //37
                                        &vars[25], &vars[37], NULL,      NULL,      //41
                                        &vars[25], &vars[37], &vars[38], NULL,      //45
                                        &vars[25], &vars[37], &vars[38], NULL,      //49
                                        &vars[31], &vars[39], NULL,      NULL,      //53
                                        &vars[31], &vars[39], &vars[40], NULL,      //57
                                        &vars[26], &vars[41], NULL,      NULL,      //61
                                        &vars[26], &vars[41], &vars[42], &vars[43], //65
                                        &vars[26], &vars[41], &vars[42], &vars[43], //69
                                        &vars[26], &vars[41], &vars[42], NULL,      //73
                                        &vars[27], &vars[44], NULL,      NULL,      //77
                                        &vars[27], &vars[44], &vars[45], NULL,      //81
                                        &vars[27], &vars[44], &vars[45], &vars[46], //85
                                        &vars[27], &vars[44], &vars[45], &vars[46], //89
                                        &vars[28], &vars[47], NULL,      NULL,      //93
                                        &vars[28], &vars[47], NULL,      NULL,      //97
                                        &vars[31], &vars[39], &vars[40], NULL,      //101
                                        &vars[29], &vars[48], &vars[49], NULL,      //105
                                        &vars[29], &vars[48], NULL,      NULL,      //109
                                        &vars[30], &vars[50], NULL,      NULL,      //113
                                        &vars[29], &vars[49], &vars[50], NULL};     //117
    
    //print variable list
    std::cout<<"\n*** Variable List ***\n\n";
    
    for(int i=1; i<21; i++)
    {
        std::cout<<"\tVariable "<<i<<": "<<varlt[i]->name<<std::endl;
    }
    std::cout<<"\nPress Enter to continue...";
    //std::cin.ignore();
    
    //print clause variable list
    std::cout<<"\n*** Clause Variable List ***\n\n";
    
    for(int i=1; i<31; i++)
    {
        std::cout<<"\n*** CLAUSE "<<i<<std::endl;
        k = 4 * (i-1);
        
        for(int j=1; j<5; j++){
            
            if(clvarlt[k+j]!=NULL){
                std::cout<<"\tVariable "<<j<<": "<<clvarlt[k+j]->name<<std::endl;
            }
            
            if(j==4){
                std::cout<<"\nPress Enter to continue...";
                //std::cin.ignore();
            }
        }
    }
    
    //print conclusion list
    std::cout<<"\n*** Conclusion List ***\n\n";
    for(int i=1; i<31; i++)
    {
        std::cout<<"\tConclusion "<<i<<": "<<conclt[i]->name<<std::endl;
    }
    std::cout<<"\nPress Enter to continue...";
    std::cin.ignore();
    
    
    std::cout<<"Answer the following questions to determine the problem:\n\n";
    
    /* For this program the problem first searched will be problem[BATDAMAGE] as it is the initial starting problem to use when dignosing a car issue*/
    
    sn=4;
    
    //statsk.push_back(sn);
    
    problem = findVar(sn,conclt,clvarlt);
    
    std::cout<<"\n\nRETURN "<<problem<<std::endl;
    
    //all variables in BC program that have not been instantiated at this point are not part of the problem set and are instantiated as false.
    for(int i =1; i<51;i++){
        if(vars[i].inst==false){
            vars[i].inst=true;
        }
    }
    
    return problem;
}


/* Forward Chaining algorithm which accepts the position of the determined problem from the Backward Chaining Aglorithm and then determines what steps to take in order to fix the issue */

int forward(int position){
    int fix =0;
    
    
    //if no problem was found
    if(position==0){
        std::cout<<"\nNo problem found to troubleshoot in this problem set. Retry or preform visual inspection to determine issue.\n";
        return 0;
    }
    
    /*List of variables used in the order in which they occur*/
    
    struct item *varlt[50] = {NULL,     &vars[22], &vars[51], &vars[23], &vars[61],
                                        &vars[24], &vars[52], &vars[1],  &vars[2],
                                        &vars[3],  &vars[53], &vars[4],  &vars[62],
                                        &vars[5],  &vars[63], &vars[6],  &vars[25],
                                        &vars[56], &vars[7],  &vars[54], &vars[8],
                                        &vars[57], &vars[9],  &vars[10], &vars[26],
                                        &vars[11], &vars[12], &vars[64], &vars[13],
                                        &vars[65], &vars[27], &vars[55], &vars[14],
                                        &vars[15], &vars[16], &vars[66], &vars[28],
                                        &vars[58], &vars[17], &vars[67], &vars[18],
                                        &vars[59], &vars[29], &vars[19], &vars[68],
                                        &vars[30], &vars[60], &vars[20], &vars[69],
                                        &vars[21]};
    
                                        //if           &&       &&    &&
    struct item *clvarlt[121] = {NULL,  &vars[22],  &vars[51], NULL, NULL,
                                        &vars[23],  &vars[61], NULL, NULL,
                                        &vars[24],  &vars[52], NULL, NULL,
                                        &vars[1],   &vars[52], NULL, NULL,
                                        &vars[2],   &vars[52], NULL, NULL,
                                        &vars[3],   &vars[53], NULL, NULL,
                                        &vars[4],   &vars[62], NULL, NULL,
                                        &vars[5],   &vars[63], NULL, NULL,
                                        &vars[6],   &vars[52], NULL, NULL,
                                        &vars[25],  &vars[56], NULL, NULL,
                                        &vars[7],   &vars[54], NULL, NULL,
                                        &vars[8],   &vars[57], NULL, NULL,
                                        &vars[9],   &vars[51], NULL, NULL,
                                        &vars[10],  NULL,      NULL, NULL,
                                        &vars[26],  &vars[56], NULL, NULL,
                                        &vars[11],  &vars[54], NULL, NULL,
                                        &vars[12],  &vars[64], NULL, NULL,
                                        &vars[13],  &vars[65], NULL, NULL,
                                        &vars[27],  &vars[55], NULL, NULL,
                                        &vars[14],  &vars[26], NULL, NULL,
                                        &vars[15],  &vars[26], NULL, NULL,
                                        &vars[16],  &vars[66], NULL, NULL,
                                        &vars[28],  &vars[58], NULL, NULL,
                                        &vars[17],  &vars[67], NULL, NULL,
                                        &vars[18],  &vars[59], NULL, NULL,
                                        &vars[29],  &vars[56], NULL, NULL,
                                        &vars[19],  &vars[68], NULL, NULL,
                                        &vars[30],  &vars[60], NULL, NULL,
                                        &vars[20],  &vars[69], NULL, NULL,
                                        &vars[21],  &vars[56], NULL, NULL};
    
    
    //print clause variable list
    std::cout<<"\n*** Variable List ***\n\n";
    
    for(int i=1; i<50; i++)
    {
        std::cout<<"\tVariable "<<i<<": "<<varlt[i]->name<<std::endl;
    }
    
    std::cout<<"\nPress Enter to continue...";
    //std::cin.ignore();
    
    //print clause variable list
    std::cout<<"\n*** Clause Variable List ***\n\n";
    
    for(int i=1; i<31; i++)
    {
        std::cout<<"*** CLAUSE "<<i<<std::endl;
        k = 4 * (i-1);
        
        for(int j=1; j<5; j++){
            
            if(clvarlt[k+j] != NULL){
                std::cout<<"\tVariable "<<j<<": "<<clvarlt[k+j]->name<<std::endl;
            }
            
            if(j==4){
                std::cout<<"\nPress Enter to continue...";
                // std::cin.ignore();
            }
        }
    }
    

    //empty vector will now use as a queue it a queue pointer
    statsk.empty();
    qp=1;
    
    //push the problem from backward chaining to queue
    statsk.push_back(position);
    
    return solve(clvarlt);
}

int findVar(int sn, struct item *conclt[], struct item *clvarlt[]){
    //push the clause number on the stack
    statsk.push_back(sn);
    int place= 0;
    bool found=false;
    
    if(sn<31 && sn>0){
        //get clauses and instantiate
        for(int i=1; i<5; i++){
            k=(sn-1)*4+i;
            if(clvarlt[k]!=NULL){
                //if is conclusion recursively find answer
                if(clvarlt[k]->pos<31){
                    //find the conclusion
                    while(found==false){
                        place++;
                        if(place<31){
                           if(!conclt[place]->inst){
                               if(conclt[place]->pos == clvarlt[k]->pos){
                                   temp=findVar(place,conclt,clvarlt);
                                   statsk.pop_back();
                                   if(temp>0){
                                       return temp;
                                
                                //statsk.push_back(place);
                                   }
                                   else{
                                       found=true;
                                   }
                               }
                               
                            }
                        }else{
                    //        std::cout<<"\n9.\n";
                            break;
                        }
                    }
                    /*if(statsk.back()!=sn){
                        temp=statsk.back();
                        statsk.pop_back();
                        temp = findVar(temp,conclt,clvarlt);
                    }*/
                }else{
                //if not conclusion check if instantiated
                instantiate(clvarlt[k]->pos, false);}
            }
            
        }
        
        s=0;
        
        //checks if statements and if true returns the problem
        switch(sn){
            case 1:{
                    conclt[sn]->inst=true;
                    if(!clvarlt[1]->value){
                        std::cout<<"\nHard to start problem set.\n";
                        conclt[sn]->value=true;
                        s=1;
                    }
                    return 0;
                    break;
            }
            case 2:{
                    conclt[sn]->inst=true;
                    if(clvarlt[5]->value && !clvarlt[6]->value){
                        std::cout<<"\nThe battery may be the issue.\n";
                        conclt[sn]->value=true;
                        s=1;
                    }
                    return 0;
                    break;
            }
            case 3:{
                    conclt[sn]->inst=true;
                    if(clvarlt[9]->value && !clvarlt[10]->value){
                        std::cout<<"\nThe starter may be the issue.\n";
                        conclt[sn]->value=1;
                        s=1;
                    
                    }
                    return 0;
                    break;
            case 4:{
                    conclt[sn]->inst=true;
                    if(clvarlt[13]->value && clvarlt[14]->value){
                        std::cout<<"\nThe problem is the battery is damaged.\n";
                        conclt[sn]->value=1;
                        s=1;
                        return 1;
                    }
                    break;
            }
            case 5:{
                    conclt[sn]->inst=true;
                    if(clvarlt[17]->value && !clvarlt[18]->value && !clvarlt[19]->value){
                        std::cout<<"\nThe problem is the battery is bad.\n";
                        conclt[sn]->value=1;
                    s=1;
                    return 2;
                }
                break;
            }
            case 6:{
                    conclt[sn]->inst=true;
                    if(clvarlt[21]->value && !clvarlt[22]->value
                       && clvarlt[23]->value && !clvarlt[24]->value){
                        std::cout<<"\nThe problem is the alternator.\n";
                        conclt[sn]->value=1;
                        s=1;
                        return 3;
                    }
                    break;
            }
            case 7:{
                    conclt[sn]->inst=true;
                    if(clvarlt[25]->value && !clvarlt[26]->value
                       && clvarlt[27]->value && clvarlt[28]->value){
                        std::cout<<"\nThe problem is the wiring is damaged.\n";
                        conclt[sn]->value=1;
                    s=1;
                    return 4;
                }
                break;
            }
            case 8:{
                conclt[sn]->inst=true;
                if(clvarlt[29]->value && !clvarlt[30]->value){
                    std::cout<<"\nThe problem is the starter.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 5;
                }
                break;
            }
            case 9:{
                conclt[sn]->inst=true;
                if(clvarlt[33]->value && clvarlt[34]->value){
                    std::cout<<"\nThe problem is the ignition switch.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 6;
                }
                break;
            }
            case 10:{
                conclt[sn]->inst=true;
                if(clvarlt[37]->value && clvarlt[38]->value){
                    std::cout<<"\nOther hard to start reasons may be issue.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 11:{
                conclt[sn]->inst=true;
                if(clvarlt[41]->value && clvarlt[42]->value){
                    std::cout<<"\nThe problem is the timing belt.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 7;
                }
                break;
            }
            case 12:{
                conclt[sn]->inst=true;
                if(clvarlt[45]->value && !clvarlt[46]->value && !clvarlt[47]->value){
                    std::cout<<"\nThe problem is the fuel pump.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 8;
                }
                break;
            }
            case 13:{
                conclt[sn]->inst=true;
                if(clvarlt[49]->value && !clvarlt[50]->value && clvarlt[51]->value){
                    std::cout<<"\nThe problem is the ignition.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 9;
                }
                break;
            }
            case 14:{
                conclt[sn]->inst=true;
                if(clvarlt[53]->value && clvarlt[54]->value){
                    std::cout<<"\nWarning light may indicate the issue.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 10;
                }
                break;
            }
            case 15:{
                conclt[sn]->inst=true;
                if(clvarlt[57]->value && !clvarlt[58]->value && clvarlt[59]->value){
                    std::cout<<"\nNeed to check if it is a handling problem.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 16:{
                conclt[sn]->inst=true;
                if(clvarlt[61]->value && clvarlt[62]->value){
                    std::cout<<"\nThe problem is the power steering.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 11;
                }
                break;
            }
            case 17:{
                conclt[sn]->inst=true;
                if(clvarlt[65]->value && !clvarlt[66]->value && !clvarlt[67]->value &&
                   !clvarlt[68]->value){
                    std::cout<<"\nThe problem is the tire pressure.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 12;
                }
                break;
            }
            case 18:{
                conclt[sn]->inst=true;
                if(clvarlt[69]->value && !clvarlt[70]->value && !clvarlt[71]->value &&
                   clvarlt[72]->value){
                    std::cout<<"\nThe problem is a flat tire.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 13;
                }
                break;
            }
            case 19:{
                conclt[sn]->inst=true;
                if(clvarlt[73]->value && !clvarlt[74]->value && clvarlt[75]->value){
                    std::cout<<"\nThe problem may be related to suspension.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 20:{
                conclt[sn]->inst=true;
                if(clvarlt[77]->value && clvarlt[78]->value){
                    std::cout<<"\nThe problem is the suspension.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 14;
                }
                break;
            }
            case 21:{
                conclt[sn]->inst=true;
                if(clvarlt[81]->value && !clvarlt[82]->value && !clvarlt[83]->value){
                    std::cout<<"\nThe problem is the wheels are out of alignment.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 15;
                }
                break;
            }
            case 22:{
                conclt[sn]->inst=true;
                if(clvarlt[85]->value && !clvarlt[86]->value && clvarlt[87]->value && clvarlt[88]->value){
                    std::cout<<"\nThe problem is the tie rod.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 16;
                }
                break;
            }
            case 23:{
                conclt[sn]->inst=true;
                if(clvarlt[89]->value && !clvarlt[90]->value && clvarlt[91]->value && !clvarlt[92]->value) {
                    std::cout<<"\nThe problem may have to do with the brakes.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 24:{
                conclt[sn]->inst=true;
                if(clvarlt[93]->value && !clvarlt[94]->value) {
                    std::cout<<"\nThe problem is the bbearings.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 17;
                }
                break;
            }
            case 25:{
                conclt[sn]->inst=true;
                if(clvarlt[97]->value && clvarlt[98]->value) {
                    std::cout<<"\nThe brakes are the issue.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 18;
                }
                break;
            }
            case 26:{
                conclt[sn]->inst=true;
                if(clvarlt[101]->value && !clvarlt[102]->value && !clvarlt[103]->value) {
                    std::cout<<"\nThe problem is more complex.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 27:{
                conclt[sn]->inst=true;
                if(clvarlt[105]->value && !clvarlt[106]->value && !clvarlt[107]->value) {
                    std::cout<<"\nThe problem is the air conditioner.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 19;
                }
                break;
            }
            case 28:{
                    conclt[sn]->inst=true;
                    if(clvarlt[109]->value && clvarlt[110]->value) {
                    std::cout<<"\nThe problem has to do with a noise.\n";
                    conclt[sn]->value=1;
                    s=1;
                }
                return 0;
                break;
            }
            case 29:{
                conclt[sn]->inst=true;
                if(clvarlt[113]->value && clvarlt[114]->value) {
                    std::cout<<"\nThe problem is the brakes are worn.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 20;
                }
                break;
            }
            case 30:{
                conclt[sn]->inst=true;
                if(clvarlt[117]->value && clvarlt[118]->value && !clvarlt[119]->value) {
                    std::cout<<"\nThe problem is not in this problem set.\n";
                    conclt[sn]->value=1;
                    s=1;
                    return 21;
                }
                break;
            }
                //if not in set of rules then return 0;
            default: return 0;
        }
        
        }
        
        
    }
    
    std::cout<<"\nPopping stack\n";
    
    temp = statsk.back()+1;
    //std::cout<<"\n"<<sn<<"\n";
    //std::cout<<"\n"<<statsk.back()<<"\n";
    

    if(statsk.back()==sn){
        
        while(temp<31){
            if(conclt[temp]->pos<22){
                if(conclt[1]->value==0){
                    return(findVar(temp, conclt, clvarlt));
                }else if(temp>13 && conclt[temp]->pos<22){
                    return(findVar(temp, conclt, clvarlt));
                }
            }else{
                temp++;
            }
        }
        if(statsk.size()==1){
            temp=statsk.back();
            k=findVar(temp, conclt, clvarlt);
            if(k>0)return k;
        }
        
    }
    //if nothing found or the clause is over the last or less than the first
    
    
    
    return 0;
}

void instantiate (int var, bool forward){
    std::cout<<"\nInstantiating\n";
    
    if(vars[var].inst==false){
        switch(var){
            case 31:
                std::cout<<"Will the car start? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 32:
                std::cout<<"Does the engine turn over? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 33:
                std::cout<<"Are the battery terminals corroded or damaged? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 34:
                std::cout<<"Does the battery hold a charge? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 35:
                std::cout<<"Does the wiring look damaged? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 36:
                std::cout<<"Does the starter work? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 37:
                std::cout<<"Does the timing belt look damaged or loose? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 38:
                std::cout<<"Is there an issue with fuel pressure? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 39:
                std::cout<<"Is the engine light on? (Y/N):";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 40:
                std::cout<<"Is it a problem with the handling of the car? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 41:
                std::cout<<"Is the wheel hard to turn? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 42:
                std::cout<<"Are the tires properly inflated? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 43:
                std::cout<<"Do the tires have a leak? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 44:
                std::cout<<"Is the suspension loose or worn? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 45:
                std::cout<<"Are the wheels aligned? (Y/N):";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 46:
                std::cout<<"Is the tie rod loose or damaged? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 47:
                std::cout<<"Do the tires spin properly? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 48:
                std::cout<<"Is the issue noise based? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 49:
                std::cout<<"Is the air from the air conditioner cool? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 50:
                std::cout<<"Is the noise high pitched? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
        }
        std::cout<<"\nInstantiation complete.\n";
    }
    if(forward==true){
        switch(var){
            case 51:
                std::cout<<"Is the key good? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 52:
                std::cout<<"Is there another battery that fixes the problem? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 53:
                std::cout<<"Does the battery hold charge? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 54:
                std::cout<<"Have you preformed a visual inspection? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 55:
                std::cout<<"Can you replicate the issue? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 56:
                std::cout<<"Is it a dangerous situation? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 57:
                std::cout<<"Is there a fuel line issue (damage, wear)? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 58:
                std::cout<<"Is there damage? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 59:
                std::cout<<"Is the brake loose? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 60:
                std::cout<<"Does it occur when stopping? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 61:
                std::cout<<"Do you have another battery on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 62:
                std::cout<<"Do you have the wire set on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 63:
                std::cout<<"Do you have another starter on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 64:
                std::cout<<"Do you have a pump on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 65:
                std::cout<<"Do you have another tire on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 66:
                std::cout<<"Do you have another tie rod on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 67:
                std::cout<<"Do you have bearings on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 68:
                std::cout<<"Do you have refrigerant on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
            case 69:
                std::cout<<"Do you have another brake pad on hand? (Y/N): ";
                std::cin>>choice;
                vars[var].value=checkChar();
                vars[var].inst=true;
                break;
        }
    }
}


int solve(struct item *clvarlt[]){
    //s as a counter
    s=0;
    while(s<121){
        sn=0;
        s++;
        k=statsk.at(qp);
        if(clvarlt[s]!=NULL){
            if(clvarlt[s]->pos==k){
                sn=((s/4)+1);
                break;
            }
        }
    }
    if(sn!=0){
        
        for(int i =1; i<5; i++){
            k=4*(sn-1)+i;
            if(clvarlt[k]!=NULL){
                instantiate(clvarlt[k]->pos,true);
            }
        }
        switch(sn){
            case 1:{
                if(clvarlt[1]->value && clvarlt[2]->value){
                    if(!vars[23].inst){
                        vars[23].inst=true;
                        vars[23].value=true;
                    }
                    std::cout<<"\nBattery Issue\n";
                }
                break;
            }
            case 2:{
                if(clvarlt[5]->value && clvarlt[6]->value){
                    if(!vars[52].inst){
                        vars[52].inst=true;
                        vars[52].value=true;
                        
                    }
                    std::cout<<"\nTest is other battery solves problem\n";
                }
                break;
            }
            case 3:{
                if(clvarlt[9]->value && !clvarlt[10]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nStarter may be broken, start there and if no fix run program again.\n";
                }
                break;
            }
            case 4:{
                if(clvarlt[13]->value && clvarlt[14]->value){
                    if(!vars[70].inst){
                        vars[70].inst=true;
                        vars[70].value=true;
                    }
                    std::cout<<"\nReplace battery to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 5:{
                if(clvarlt[17]->value && clvarlt[18]->value){
                    if(!vars[71].inst){
                        vars[71].inst=true;
                        vars[71].value=true;
                    }
                    std::cout<<"\nReplace battery to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 6:{
                if(clvarlt[21]->value && clvarlt[22]->value){
                    if(!vars[72].inst){
                        vars[72].inst=true;
                        vars[72].value=true;
                    }
                    std::cout<<"\nReplace alternator to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 7:{
                if(clvarlt[25]->value && clvarlt[26]->value){
                    if(!vars[73].inst){
                        vars[73].inst=true;
                        vars[73].value=true;
                    }
                    std::cout<<"\nReplace or fix damaged wires to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 8:{
                if(clvarlt[29]->value && clvarlt[30]->value){
                    if(!vars[74].inst){
                        vars[74].inst=true;
                        vars[74].value=true;
                    }
                    std::cout<<"\nReplace starter to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 9:{
                if(clvarlt[33]->value && !clvarlt[34]->value){
                    if(!vars[75].inst){
                        vars[75].inst=true;
                        vars[75].value=true;
                    }
                    std::cout<<"\nReplace ignition switch to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 10:{
                if(clvarlt[37]->value && !clvarlt[38]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nPreform a visual inspection, if able to find other symptoms restart troubleshooting program.\n";
                }
                break;
            }
            case 11:{
                if(clvarlt[41]->value && clvarlt[42]->value){
                    if(!vars[76].inst){
                        vars[76].inst=true;
                        vars[76].value=true;
                    }
                    std::cout<<"\nReplace timing belt to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 12:{
                if(clvarlt[45]->value && !clvarlt[46]->value){
                    if(!vars[77].inst){
                        vars[77].inst=true;
                        vars[77].value=true;
                    }
                    std::cout<<"\nReplace fuel pump to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 13:{
                if(clvarlt[49]->value && clvarlt[50]->value){
                    if(!vars[78].inst){
                        vars[78].inst=true;
                        vars[78].value=true;
                    }
                    std::cout<<"\nReplace ignition to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 14:{
                if(clvarlt[53]->value){
                    if(!vars[89].inst){
                        vars[89].inst=true;
                        vars[89].value=true;
                    }
                    std::cout<<"\nRun warning light inspection to determine problem, restart troubleshooting program with information gathered or proceed based on reccomendations.\n";
                }
                break;
            }
            case 15:{
                if(clvarlt[57]->value && !clvarlt[58]->value){
                    if(!vars[55].inst){
                        vars[55].inst=true;
                        vars[55].value=true;
                    }
                    std::cout<<"\nAttempt to replicate the issue. Program will continue assuming you were able to.\n";
                }
                break;
            }
            case 16:{
                if(clvarlt[61]->value && clvarlt[62]->value){
                    if(!vars[82].inst){
                        vars[82].inst=true;
                        vars[82].value=true;
                    }
                    std::cout<<"\nFix power steering to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 17:{
                if(clvarlt[65]->value && clvarlt[66]->value){
                    if(!vars[83].inst){
                        vars[83].inst=true;
                        vars[83].value=true;
                    }
                    std::cout<<"\nProperly inflate tires to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 18:{
                if(clvarlt[69]->value && clvarlt[70]->value){
                    if(!vars[79].inst){
                        vars[79].inst=true;
                        vars[79].value=true;
                    }
                    std::cout<<"\nReplace flat tire(s) to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 19:{
                if(clvarlt[73]->value && clvarlt[74]->value){
                    if(!vars[26].inst){
                        vars[26].inst=true;
                        vars[26].value=true;
                    }
                    std::cout<<"\nCheck handling of vehicle. Program will continue assuming issue with handling.\n";
                }
                break;
            }
            case 20:{
                if(clvarlt[77]->value && clvarlt[78]->value){
                    if(!vars[84].inst){
                        vars[84].inst=true;
                        vars[84].value=true;
                    }
                    std::cout<<"\nFix suspension to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 21:{
                if(clvarlt[81]->value && clvarlt[82]->value){
                    if(!vars[85].inst){
                        vars[85].inst=true;
                        vars[85].value=true;
                    }
                    std::cout<<"\nRealign wheels to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 22:{
                if(clvarlt[85]->value && clvarlt[86]->value){
                    if(!vars[81].inst){
                        vars[81].inst=true;
                        vars[81].value=true;
                    }
                    std::cout<<"\nReplace tie rod to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 23:{
                if(clvarlt[89]->value && !clvarlt[90]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nPreform a visual inspection, if able to find other symptoms restart troubleshooting program.\n";
                }
                break;
            }
            case 24:{
                if(clvarlt[93]->value && clvarlt[94]->value){
                    if(!vars[86].inst){
                        vars[86].inst=true;
                        vars[86].value=true;
                    }
                    std::cout<<"\nFix bearings to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 25:{
                if(clvarlt[97]->value && clvarlt[98]->value){
                    if(!vars[87].inst){
                        vars[87].inst=true;
                        vars[87].value=true;
                    }
                    std::cout<<"\nFix brake(s) to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 26:{
                if(clvarlt[101]->value && !clvarlt[102]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nPreform a visual inspection, if able to find other symptoms restart troubleshooting program.\n";
                }
                break;
            }
            case 27:{
                if(clvarlt[105]->value && clvarlt[106]->value){
                    if(!vars[88].inst){
                        vars[88].inst=true;
                        vars[88].value=true;
                    }
                    std::cout<<"\nFix A/C to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 28:{
                if(clvarlt[109]->value && clvarlt[110]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nPreform a visual inspection, if able to find other symptoms restart troubleshooting program.\n";
                }
                break;
            }
            case 29:{
                if(clvarlt[113]->value && clvarlt[114]->value){
                    if(!vars[80].inst){
                        vars[80].inst=true;
                        vars[80].value=true;
                    }
                    std::cout<<"\nReplace brake(s) to solve problem, if doesn't resolve restart troubleshooting program.\n";
                }
                break;
            }
            case 30:{
                if(clvarlt[117]->value && !clvarlt[118]->value){
                    if(!vars[54].inst){
                        vars[54].inst=true;
                        vars[54].value=true;
                    }
                    std::cout<<"\nPreform a visual inspection, if able to find other symptoms restart troubleshooting program.\n";
                }
                break;
            }
            default:{
                return 0;
            }
        }
        
    }
    
    if(qp!=statsk.back()){
        qp++;
        solve(clvarlt);
    }
    return 0;
}

//recursively checks if choice is a valid entry and returns when a valid choice is made
bool checkChar(){
    bool value=false;
    
    if(choice == 1 || choice =='y' || choice == 'Y'){
        value= true;
    }else if (choice == 0 || choice == 'n' || choice == 'N'){
        value= false;
    }
    else{
        std::cout<<"Invalid Input. Please enter Y or N: ";
        std::cin>>choice;
        checkChar();
    }
    return value;
}

