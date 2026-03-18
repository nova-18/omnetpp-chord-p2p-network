simple Client
{
    gates :
        input in[];
        output out[];
}

network myNetwork
{
    parameters :
        
        int numClients;
        
    	
	submodules :
		c0 : Client { @display("p=100,0") ;}
		c1 : Client { @display("p=62,78") ;}
		c2 : Client { @display("p=-22,97") ;}
		c3 : Client { @display("p=-90,43") ;}
		c4 : Client { @display("p=-90,-43") ;}
		c5 : Client { @display("p=-22,-97") ;}
		c6 : Client { @display("p=62,-78") ;}

	connections :

		c0.out++ --> { delay = 100ms; } --> c1.in++ ;
		c0.out++ --> { delay = 100ms; } --> c2.in++ ;
		c0.out++ --> { delay = 100ms; } --> c4.in++ ;
		c1.out++ --> { delay = 100ms; } --> c2.in++ ;
		c1.out++ --> { delay = 100ms; } --> c3.in++ ;
		c1.out++ --> { delay = 100ms; } --> c5.in++ ;
		c2.out++ --> { delay = 100ms; } --> c3.in++ ;
		c2.out++ --> { delay = 100ms; } --> c4.in++ ;
		c2.out++ --> { delay = 100ms; } --> c6.in++ ;
		c3.out++ --> { delay = 100ms; } --> c4.in++ ;
		c3.out++ --> { delay = 100ms; } --> c5.in++ ;
		c3.out++ --> { delay = 100ms; } --> c0.in++ ;
		c4.out++ --> { delay = 100ms; } --> c5.in++ ;
		c4.out++ --> { delay = 100ms; } --> c6.in++ ;
		c4.out++ --> { delay = 100ms; } --> c1.in++ ;
		c5.out++ --> { delay = 100ms; } --> c6.in++ ;
		c5.out++ --> { delay = 100ms; } --> c0.in++ ;
		c5.out++ --> { delay = 100ms; } --> c2.in++ ;
		c6.out++ --> { delay = 100ms; } --> c0.in++ ;
		c6.out++ --> { delay = 100ms; } --> c1.in++ ;
		c6.out++ --> { delay = 100ms; } --> c3.in++ ;
}