# Steps to run :

1)Please ensure that a python version 3 .8 and above is installed on the machine. Also install and setup omnet++ 6.1.
2)Edit the topology.txt file for network topology. It is structured similar to python dictionary, and the delays are in ms.
Make sure it is accurate with the connection delay values matching the clients declared earlier.
3)Run the networkManager.py file using 
'''
python3 networkManager.py
'''
4)It will prompt to ask the number of tasks to be scheduled please enter an integer value.
5)open the project in omnet++ and run using the run button. please do not edit anything else.
4)Please make sure to run the python script first before rerunning the simulation in omnet++