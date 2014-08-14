//
//  main.cpp
//  Computational1
//
//  Created by federica palla and thomas bronzwaer on 17/02/14.
//  Copyright (c) 2014 federica. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/*
#ifndef ROOT_H
#define ROOT_H
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TF1.h"
#endif
*/

#include "mt19937-64.h"

const int NSTEPS = 2 ;
int ns;
const int NWALKSPERGROUP=1000;
const int NGROUPS = 300; // NTRIALS is split into NGROUPS sub-groups
int *xposArray;
int *xposSquaredArray;
int *yposArray;
int *yposSquaredArray;


int xPos = 0;
int yPos = 0;
const double stepSize = 0.1;

using namespace std;

// COMPLETE ONE RANDOM WALK
void trial(){
    xPos = 0;
    yPos = 0;
    double random = 0.;
    
    for (int i = 0; i < ns ; i++){
        
        random = genrand64_real1();
        
        if (random < 0.25){
            xPos--;
        }
        else if(random < 0.5){
            xPos++;
        }
        else if(random < 0.75){
            yPos--;
        }
        else {
            yPos++;
        }
        
        xposArray[i] += xPos;
        yposArray[i] += yPos;
        xposSquaredArray[i] += xPos * xPos;
        yposSquaredArray[i] += yPos * yPos;
    }
}

int main() {
    
    //TApplication app("App",0,0);
    
    
    // Initialize the RNG & console precision
    unsigned long long seed = 9956ull;
    init_genrand64(seed);
    std::cout.precision(15);
    
    int cont=NSTEPS*2, counter=0;
    double nsteps[6];
    
    double *xallgroups = new double[6 * NGROUPS];
    double *yallgroups = new double[6 * NGROUPS];
    for (int i = 0; i < 6 * NGROUPS; i++){
        xallgroups[i] = 0.;
        yallgroups[i] = 0.;
    }

    for (int i = 0; i < 6; i++){
        nsteps[i] = 0.;
    }
    
    ns=NSTEPS;
        
    for (int jj = 0; jj < NGROUPS; jj++){
        
        // reset the arrays
        
        cont=NSTEPS;
        counter=0;
    
        for (int j= NSTEPS; j< (int)pow(NSTEPS,8); j = cont){

            ns=j;
            xposArray = new int[ns];
            yposArray = new int[ns];
            xposSquaredArray = new int[ns];
            yposSquaredArray = new int[ns];

            for (int k = 0; k < j; k++){
                xposArray[k] = 0.;
                yposArray[k] = 0.;
                xposSquaredArray[k] = 0.;
                yposSquaredArray[k] = 0.;
            }


            // Do all the walks in one group
            for (int i = 1; i <= NWALKSPERGROUP; i++){

                trial();

                // Only plot when they're all done
                if (i == NWALKSPERGROUP){

                    // Calculate <Dx> and <Dy> FOR THIS GROUP
                    cout<<"\n\nN = "<<j<<endl;         
                    cout << "\nxPos = " << (double) xposArray[j-1] / i;
                    cout << "\nyPos = " << (double) yposArray[j-1] / i;           
                    cout << "\n\nVar(xPos) = " << (double) ((xposSquaredArray[j-1] / (double) i) - (xposArray[j-1] / (double) i) * (xposArray[j-1] / (double) i));
                    cout << "\nVar(yPos) = " << (double) (yposSquaredArray[j-1] / (double) i) - (yposArray[j-1] / (double) i) * (yposArray[j-1] / (double) i);      
 
                    // These 2D arrays contain the SUMS of the <Dx^2> and <Dy^2> FOR ALL GROUPS
                    xallgroups[6 * jj + counter] = (double) (xposSquaredArray[j-1] / (double) i) - (xposArray[j-1] / (double) i) * (xposArray[j-1] / (double) i);
                    yallgroups[6 * jj + counter] = (double) (yposSquaredArray[j-1] / (double) i) - (yposArray[j-1] / (double) i) * (yposArray[j-1] / (double) i);

                }       
            }


            nsteps[counter]=j;
            cont= cont*2;
            counter ++;
            
            
            memset(xposArray, 0, sizeof(xposArray));
            memset(yposArray, 0, sizeof(xposArray));
            memset(xposSquaredArray, 0, sizeof(xposArray));
            memset(yposSquaredArray, 0, sizeof(xposArray));

        }
    }
    
    cout <<endl;
    
    double *xgroupaverages = new double[6];
    double *ygroupaverages = new double[6];
    double *Rgroupaverages = new double[6];
    double *histogramarray = new double[NGROUPS];
    double *xgroupvar = new double[6];
    double *ygroupvar = new double[6];
    
    for (int q = 0; q < 6; q++){
        
        for (int qq = 0; qq < NGROUPS; qq++ ){
            xgroupaverages[q] += xallgroups[q + qq * 6];
            ygroupaverages[q] += yallgroups[q + qq * 6];
            histogramarray[qq] = xallgroups[5 + qq * 6];
        }
        xgroupaverages[q] /= NGROUPS;
        ygroupaverages[q] /= NGROUPS;
        Rgroupaverages[q] = xgroupaverages[q] + ygroupaverages[q];
        cout << "\nxgroupaverages " << (int) q << " = " << (double) xgroupaverages[q];
        cout << "\nygroupaverages " << (int) q << " = " << (double) ygroupaverages[q];
        cout << "\nRgroupaverages " << (int) q << " = " << (double) Rgroupaverages[q];
    }
    
    for (int i = 0; i < NGROUPS; i++){
        cout << "\n BLAAAT " << histogramarray[i];
    }
    
    for (int q = 0; q < 6; q++){      
        for (int qq = 0; qq < NGROUPS; qq++ ){
            xgroupvar[q] += (xallgroups[q + qq * 6] - xgroupaverages[q]) * (xallgroups[q + qq * 6] - xgroupaverages[q]);
            ygroupvar[q] += (yallgroups[q + qq * 6] - ygroupaverages[q]) * (yallgroups[q + qq * 6] - ygroupaverages[q]);
        }
        xgroupvar[q] /= (NGROUPS - 1);
        ygroupvar[q] /= (NGROUPS - 1);
        
        //cout << "\nxgroupvar " << (int) q << " = " << (double) xgroupvar[q];
        //cout << "\nygroupvar " << (int) q << " = " << (double) ygroupvar[q];

    }

    
	/*
    TCanvas *values = new TCanvas ("errors","XSigma trend", 1000., 1000.);
    TGraph *g1 = new TGraph(6,nsteps,xplot);
    //TAxis *xaxis = g1->GetXaxis();
    //xaxis->SetLimits(0.,500000);
    //TAxis *yaxis = g1->GetYaxis();
    //yaxis->SetLimits(0,6);
    g1 ->SetLineColor(2);
    values->cd();
    g1->Draw("A*");
    TF1 *powerlaw= new TF1("Power_law", "pow(x,[0])" , 0.,1000.);
    g1 -> Fit(powerlaw , "Q");
    g1->Draw("Same");
    values->cd();

    //double a=powerlaw->GetParameter(0);
    //double mu=powerlaw->GetParameter(1);
    
    TCanvas *values1 = new TCanvas ("errors1","YSigma trend", 1000., 1000.);
    TGraph *g2 = new TGraph(6,nsteps,yplot);
    //TAxis *xaxis = g1->GetXaxis();
    //xaxis->SetLimits(0.,500000);
    //TAxis *yaxis = g1->GetYaxis();
    //yaxis->SetLimits(0,6);
    g2 ->SetLineColor(2);
    values1->cd();
    g2->Draw("A*");
    TF1 *powerlaw1= new TF1("Power_law", "pow(x,[0])" , 0.,1000.);
    g2 -> Fit(powerlaw1 , "Q");
    g2->Draw("Same");
    values1->cd();
    
    //double b=powerlaw1->GetParameter(0);
    //double nu=powerlaw1->GetParameter(1);
    
  
   
    
    
    app.Run();
    */
    return 0;
}

