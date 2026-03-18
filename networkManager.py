import re
import ast
import os
import math

def generate_circular_submodules(num: int, radius: int = 100) -> list[str]:
    submodules = []
    angle_step = 2 * math.pi / num

    for i in range(num):
        angle = i * angle_step
        x = round(radius * math.cos(angle))
        y = round(radius * math.sin(angle))
        submodules.append(f'c{i} : Client {{ @display("p={x},{y}") ;}}')

    return submodules

def parse_topology_file(filename):
    data = {}
    data_List = []
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line or line.startswith("#") or line == "":  # Ignore empty lines and comments
                continue
            data_List.append(line)
        
    
    for i in range(len(data_List)):
        element = data_List[i]
        if(element == 'parameters'):
            inp = data_List[i+2]
            client_count = int(inp.split(' ')[-1])
            data['numClient'] = client_count
        
        elif(element == 'client -> client delay'):
            inp = [int(val) for val in data_List[i+2][1:-1].split(',')]
            data['delayList'] = inp

    return data

def createConns(topo):
    clientsc = topo['numClient']
    delays = topo['delayList']
    bits = 0
    val = 1
    while(val < clientsc):
        val *=2 
        bits +=1
    
    connLis = []

    for node in range(clientsc):
        MOD = clientsc
        
        for bit in range(bits):
            dest = (node + 2 ** bit) % MOD 
            cmd = f"c{node}.out++ --> {{ delay = {delays[node]}ms; }} --> c{dest}.in++ "
            connLis.append(cmd)

    return connLis

def edit_ned_file(file_path,submodules_lis,connections_lis):

    try:
        # Read the input file
        with open(file_path, 'r') as file:
            lines = file.readlines()

        # print(lines)
        
        final_lis = []

        index1, index2 = 0,0
        for i,line in enumerate(lines):
            if 'submodules' in line.lower():
                index1 = i
                break
        
        for i,line in enumerate(lines):
            if 'connections' in line.lower():
                index2 = i
                break

        for i in range(index1,index2):
            final_lis.append(lines[i])

        # print(final_lis)
        final_lis = final_lis[:1]
        submodules_lis = ['\t\t' + submod + '\n' for submod in submodules_lis]
        
        for submod in submodules_lis:
            final_lis.append(submod)

        final_lis.append('\n')
        final_lis.append('\tconnections :\n')
        final_lis.append('\n')

        connections_lis = ['\t\t' + conn + ';\n' for conn in connections_lis]

        for conn in connections_lis:
            final_lis.append(conn)

        final_lis.append('}')

        output_lines = (
            lines[:index1] +  # Keep the 'connections:' line
            final_lis            # Add new connections with proper indentation          # Keep the closing brace and any following lines
        )
        # print(output_lines)
    
        with open(file_path, 'w') as file:
            file.writelines(output_lines)
        
        print(f"Successfully edited connections in {file_path}")
    
    except IOError as e:
        print(f"Error reading or writing file: {e}")
    except ValueError as e:
        print(f"Error processing file: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

def edit_ini_file(file_path, num_clients):
  
    try:
        # Read the input file
        with open(file_path, 'r') as file:
            lines = file.readlines()
        
        # Create a copy of lines to modify
        output_lines = []
        
        # Flag to track if we're in the [General] section
        in_general_section = False
        
        # Process each line
        for line in lines:
            # Check for section headers
            if line.strip().startswith('['):
                in_general_section = line.strip() == '[General]'
            
            # If in General section, modify specific parameters
            if in_general_section:

                if '**.numClients' in line:
                    output_lines.append(f"**.numClients = {num_clients}\n")
                else:
                    output_lines.append(line)
            else:
                # Keep lines outside General section unchanged
                output_lines.append(line)
        
        # Write the modified content back to the same file
        with open(file_path, 'w') as file:
            file.writelines(output_lines)
        
        print(f"Successfully edited parameters in {file_path}")
    
    except IOError as e:
        print(f"Error reading or writing file: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

file_path = "topology.txt"
topology = parse_topology_file(file_path)
# print(topology)


ned_file = "network.ned"
ini_file = "omnetpp.ini"
connections_list = createConns(topology)
submod_lis = generate_circular_submodules(topology['numClient'])

# print(generate_circular_submodules())
edit_ini_file(ini_file, topology['numClient'])
edit_ned_file(ned_file,submod_lis,connections_list)
# edit_ned_connections(ned_file, connections_list)


# Define log directory and file names
file_path = "logs.log"

# Open the file in write mode ('w') — this creates the file if it doesn't exist,
# and wipes the contents if it does.
with open(file_path, 'w') as f:
    pass 
# log_dir = "logs"
# log_files = ["client.log", "server.log", "gossip.log"]

# log_dir = "logs"
# log_files = ["client.log", "server.log", "gossip.log"]

# # Create logs directory if it doesn't exist
# if not os.path.exists(log_dir):
#     os.makedirs(log_dir)
#     print(f"Created directory: {log_dir}")

# # Create or wipe log files
# for log_file in log_files:
#     log_path = os.path.join(log_dir, log_file)
#     with open(log_path, "w") as f:  # Open in write mode to wipe existing content
#         f.write("")  
#     print(f"Wiped/Created file: {log_path}")



# # Ask the user for Total_Task_Count using a prompt
try:
    Total_Task_Count = int(input("Enter the Total Task Count (integer value): "))
    
    # Generate config.h
    with open('config.h', 'w') as f:
        f.write(f'#ifndef CONFIG_H\n#define CONFIG_H\n\nconst int Total_Task_Count = {Total_Task_Count};\n\n#endif')
    
    print(f"config.h generated with Total_Task_Count = {Total_Task_Count}")
except ValueError:
    print("Invalid input! Please enter an integer.")


