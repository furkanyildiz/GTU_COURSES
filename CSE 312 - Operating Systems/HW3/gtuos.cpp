#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>


GTUOS::~GTUOS(){
    if(TEST_DEBUG){std::cout<<"destructure"<<std::endl;}

    //save structures

    std::ofstream output_file(file_system_file_name, std::ios::binary);
    output_file.write((char*)&blocks, sizeof(blocks));
    output_file.write((char*)&files, sizeof(files));
    output_file.write((char*)&file_count, sizeof(file_count));
    output_file.write((char*)&is_there_free_block, sizeof(is_there_free_block));

    output_file.close();

    if(this->DEBUG == 0 || this->DEBUG == 1){
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        std::cout<<"The Directory Informations: \n";
        for (int i = 0; i < file_count; ++i) {
            std::cout << "Filename: " << files[i].filename;
            std::cout << ", Creation Time: " << files[i].creation_time;
            std::cout << ", Last Modification Time: " << files[i].last_modification_time;
            std::cout << ", Last Access Time: " << files[i].last_access_time;
            std::cout << ", Size: " << files[i].size;
            std::cout << ", File Pointer: " << files[i].file_pointer;
            std::cout << std::endl;
            std::cout << "----------"<<std::endl;
        }
        std::cout << "--------------------------------------------------------------------------" << std::endl;
    }




}

GTUOS::GTUOS(CPU8080* cpu8080,uint64_t* cycle_c,int debug,const char* file_system_file_name_) {
    theCPU = cpu8080;
    cycle_count = cycle_c;
    uint64_t  quantum_t = 100;
    scheduler = Scheduler(theCPU,cycle_c,quantum_t,debug);
    returnState = theCPU->state;
    file_system_file_name = file_system_file_name_;
    this->DEBUG = debug;

    /* Obtain current time. */
    current_time = time(NULL);

/*

    for (int i = 0; i<BLOCK_CAP; ++i){q1w2
        memset(&files[i], 0, sizeof(files[i]));
        memset(&blocks[i], 0, sizeof(blocks[i]));
        blocks[i].block_num = i;
        blocks[i].owner = -1;
    }
    file_count = 0;
    is_there_free_block = 1;
*/


    std::ifstream input_file(file_system_file_name, std::ios::binary);
    input_file.read((char*)&blocks, sizeof(blocks));
    input_file.read((char*)&files, sizeof(files));
    input_file.read((char*)&file_count, sizeof(file_count));
    input_file.read((char*)&is_there_free_block, sizeof(is_there_free_block));

    input_file.close();




}


uint64_t GTUOS::handleCall(uint64_t *cycle, bool * context_switch){

    setContext_switch_happen(false);
    uint64_t  calling_pc = scheduler.get_called_os_pc();

    //update runnig thread with the calling pc
    scheduler.update_pc(calling_pc+3,*cycle_count);

    uint64_t cycle_of_call;

    switch(theCPU->state->a){

        case PRINT_B: cycle_of_call = handlePrintB(); break;
        case PRINT_MEM: cycle_of_call = handlePrintMem(); break;
        case READ_B: cycle_of_call = handleReadB(); break;
        case READ_MEM: cycle_of_call = handleReadMem(); break;
        case PRINT_STR:cycle_of_call =  handlePrintStr(); break;
        case READ_STR:cycle_of_call =  handleReadStr(); break;
        case GET_RND: cycle_of_call = handleGetRnd(); break;
        case TEXIT: cycle_of_call = handleTExit(cycle); break;
        case TJOIN: cycle_of_call = handleTJoin(cycle); break;
        case TYIELD: cycle_of_call = handleTYield(cycle); break;
        case TCREATE: cycle_of_call = handleTCreate(cycle); break;

        case FileCreate: cycle_of_call = handleFileCreate(); break;
        case FileClose: cycle_of_call = handleFileClose(); break;
        case FileOpen: cycle_of_call = handleFileOpen(); break;
        case FileRead: cycle_of_call = handleFileRead(); break;
        case FileWrite: cycle_of_call = handleFileWrite(); break;
        case FileSeek: cycle_of_call = handleFileSeek(); break;
        case DirRead: cycle_of_call = handleDirRead(); break;



        default: std::cout<<"Invalid System Call!"<<(int)theCPU->state->a<<std::endl; cycle_of_call = 0;

    }




    //Print contents of the file table
    if(DEBUG == 1) {
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        std::cout << "The contents of the open files: \n";
        for (int i = 0; i < open_files_table.size(); ++i) {
            std::cout << "Filename: " << open_files_table[i]->filename;
            std::cout << ", Creation Time: " << open_files_table[i]->creation_time;
            std::cout << ", Last Modification Time: " << open_files_table[i]->last_modification_time;
            std::cout << ", Last Access Time: " << open_files_table[i]->last_access_time;
            std::cout << ", Size: " << open_files_table[i]->size;
            std::cout << ", File Pointer: " << open_files_table[i]->file_pointer;
            std::cout << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------" << std::endl;
    }
    *context_switch = is_context_switch_happen();
    return cycle_of_call;
}

uint64_t GTUOS::handleFileCreate() {
    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FCREATE"<<std::endl;}

    //check error
    if (file_count == 4096 || is_there_free_block != 1) {
        if(TEST_DEBUG){std::cout<<"FCREATE ERROR"<<std::endl;}

        theCPU->state->b = (uint8_t) 0;
        return 0;
    }


    char *c_time_string;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    if(TEST_DEBUG){std::cout<<"fcreate address: "<<address <<std::endl;}
    int index = 0;
    bool Flag = true;


    while (Flag)
        if (theCPU->memory->at(address) == '\0')
            Flag = false;
        else
            files[file_count].filename[index++] = theCPU->memory->at(address++);

    files[file_count].filename[index] = '\0';

    // eğer aynı dosya adından bir tane daha açılırsa, onun sonuna count eklenir.
    int m = 0;
    for(int i=0; i<file_count; ++i){
        if(strcmp(files[i].filename, files[file_count].filename ) == 0)
            m++;
    }
    if(m>1){
        files[file_count].filename[index++] = m + 48;
        files[file_count].filename[index] = '\0';
    }



    if(TEST_DEBUG){std::cout<<"created file, its name: ";
        int m=0;
        while(files[file_count].filename[m] != '\0')
            std::cout<<files[file_count].filename[m++];
        std::cout<<std::endl;
    }

    c_time_string = ctime(&current_time);
//    files[file_count].creation_time = *cycle_count;
//    files[file_count].last_modification_time = *cycle_count;
//    files[file_count].last_access_time = *cycle_count;

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    sprintf (files[file_count].creation_time, "%s.%09ld", buff, ts.tv_nsec);
    sprintf (files[file_count].last_modification_time, "%s.%09ld", buff, ts.tv_nsec);
    sprintf (files[file_count].last_access_time, "%s.%09ld", buff, ts.tv_nsec);


    files[file_count].file_pointer = 0;
    files[file_count].size = 0;
    files[file_count].fileID = (file_count+3);

    //give first empty block(in contigous memory) to new file.
    for(int i=0; i<BLOCK_CAP; ++i){
        if (blocks[i].is_in_use == 0){
            blocks[i].is_in_use = 1;
            blocks[i].owner = file_count;

            //////////////
            files[file_count].alloc_block_num = 1;
            //files[file_count].blocks.push_back(i);
            files[file_count].alloc_blocks[0] = i;
            ///////////////
            break;
        }
    }


    file_count++;
    theCPU->state->b = (uint8_t) 1;
    return FCREATE_CYCLE;
}

uint64_t GTUOS::handleFileOpen() {
    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FOPEN"<<std::endl;}

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;
    if(TEST_DEBUG){std::cout<<"file open address: "<<address <<std::endl;}

    char* c_time_string;

    int index=0;
    bool Flag = true;
    char open_file_name[100];
    memset(&open_file_name, 0, sizeof(open_file_name));

    while (Flag)
        if (theCPU->memory->at(address) == '\0')
            Flag = false;
        else
            open_file_name[index++] = theCPU->memory->at(address++);

    open_file_name[index] = '\0';
    struct timespec ts;
    char buff[100];

    //find in created files
    bool is_file_found = false; // is the file has created?
    int the_file = -1 ;
    int i=0;
    for(; i<file_count && !is_file_found; ++i){
        if ( strcmp(files[i].filename, open_file_name) == 0){
            the_file = i;
            c_time_string = ctime(&current_time);
//            files[the_file].last_access_time = *cycle_count;

            timespec_get(&ts, TIME_UTC);
            strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
            sprintf (files[the_file].last_access_time, "%s.%09ld", buff, ts.tv_nsec);

            open_files_table.push_back(&files[the_file]);
            is_file_found = true;
        }

    }
    if (!is_file_found){ //the file has not created
        if(TEST_DEBUG){std::cout<<"FOPEN ERROR"<<std::endl;}

        theCPU->state->b = (uint8_t) 0;
        return 0;
    }
    theCPU->state->b = (uint8_t) files[the_file].fileID;
    if(TEST_DEBUG){std::cout<<"opened file, its handleID: "<<(int)theCPU->state->b<<std::endl;}


    return FOPEN_CYCLE;
}
uint64_t GTUOS::handleFileClose() {

    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FCLOSE"<<std::endl;}


    int handleID = theCPU->state->b;

    bool find_file = false;
    int i =0;
    for (; i<open_files_table.size() && !find_file; ++i) {
        if (open_files_table[i]->fileID == handleID) {
            find_file = true;

            open_files_table[i]->file_pointer = 0;
        }
    }

    if (find_file) {

        open_files_table.erase(open_files_table.begin() + (i - 1));
        theCPU->state->b = (uint8_t) 1;

    }
    else{
        if(TEST_DEBUG){std::cout<<"FCLOSE ERROR"<<std::endl;}

        theCPU->state->b = (uint8_t) 0;
        return 0;
    }

    return FCLOSE_CYCLE;

}
uint64_t GTUOS::handleFileWrite() {
    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FWRITE"<<std::endl;}

    uint32_t buffer_address;
    buffer_address = (theCPU->state->b << 8) | theCPU->state->c;
    int number_of_bytes = theCPU->state->d;
    int handleID = theCPU->state->e;


    bool find_file = false;
    int the_file;
    int i = 0;
    for (; i < open_files_table.size() && !find_file; ++i) {
        if (open_files_table[i]->fileID == handleID) {

            for(int j=0; j<file_count && !find_file; ++j){
                if (files[j].fileID == handleID) {
                    the_file = j;
                    find_file = true;

                }
            }
        }
    }

    if (!find_file) {
        theCPU->state->b = (uint8_t) 0;
        if(TEST_DEBUG){std::cout<<"FWRITE ERROR"<<std::endl;}

        return 0;
    }

    int nth_write_block = files[the_file].file_pointer / BLOCK_SIZE;
    int write_block_num = files[the_file].alloc_blocks[nth_write_block];


    //write data
    if(TEST_DEBUG){std::cout<<"fwrite data: ";}

    int writed_count = 0;
    bool need_new_block_to_write = false;
    if (number_of_bytes > 0) {
        for (int i = files[the_file].file_pointer%BLOCK_SIZE; i < BLOCK_SIZE && number_of_bytes > writed_count; ++i) {

            int write_data = theCPU->memory->at(buffer_address++);
            if(TEST_DEBUG){std::cout<<(char)write_data;}

            blocks[write_block_num].data[i] = write_data;
            if (i>blocks[write_block_num].size)
                blocks[write_block_num].size++;
            writed_count++;

        }
    }
    if ( number_of_bytes > writed_count) {
        need_new_block_to_write = true;
    }
    if(TEST_DEBUG){std::cout<<"\n";}

    if(need_new_block_to_write){ //yazılacak sey bloga sigmadiysa
        if(TEST_DEBUG){std::cout<<"NEW ALLOC2"<<std::endl;}

        int new_block = alloc_new_block(the_file);
        if (new_block != -1) {
            int i = 0;
            while (writed_count != number_of_bytes) {

                int write_data = theCPU->memory->at(buffer_address++);

                blocks[new_block].data[i++] = write_data;
                blocks[new_block].size++;
                writed_count++;
                if (blocks[new_block].size >= BLOCK_SIZE) {
                    i = 0;
                    new_block = alloc_new_block(the_file);
                    if (new_block == -1) break; //No more memory
                }

            }
        }
    }
    //update size
    int total_size = 0;
    for(int i=0; i<files[the_file].alloc_block_num; ++i){

        int block_num = files[the_file].alloc_blocks[i];
        total_size += blocks[block_num].size;

    }
    files[the_file].size = total_size;
    //It advances the file pointer by the number of bytes written.
    files[the_file].file_pointer+=writed_count;
//    files[the_file].last_modification_time = *cycle_count;
//    files[the_file].last_access_time = *cycle_count;
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    char temp[30];
    memset(&buff, 0, sizeof(buff));
    memset(&temp, 0, sizeof(temp));
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    sprintf (temp, "%s.%09ld", buff, ts.tv_nsec);
    memset(&files[the_file].last_modification_time, 0, sizeof(files[file_count].last_modification_time));
    strcpy(files[the_file].last_modification_time,temp);
    sprintf (files[the_file].last_access_time, "%s.%09ld", buff, ts.tv_nsec);


    theCPU->state->b = (uint8_t) writed_count;


    return FWRITE_CYCLE;
}

uint64_t GTUOS::handleFileRead() {

    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FREAD"<<std::endl;}

    uint32_t buffer_address;
    buffer_address = (theCPU->state->b << 8) | theCPU->state->c;
    int number_of_bytes = theCPU->state->d;
    int handleID = theCPU->state->e;

    bool find_file = false;
    int the_file;
    int i = 0;
    for (; i < open_files_table.size() && !find_file; ++i) {
        if (open_files_table[i]->fileID == handleID) {

            for(int j=0; j<file_count&& !find_file; ++j){
                if (files[j].fileID == handleID) {
                    the_file = j;
                    find_file = true;

                }
            }
        }
    }

    if (!find_file) {
        theCPU->state->b = (uint8_t) 0;
        return 0;
    }

    int readed_count = 0;
    int nth_read_block = files[the_file].file_pointer / BLOCK_SIZE;
    int read_block_num = files[the_file].alloc_blocks[nth_read_block];
    bool null_found = false;
    for(int i= files[the_file].file_pointer % BLOCK_SIZE; i<BLOCK_SIZE && readed_count < number_of_bytes && readed_count<=files[the_file].size; ++i){

        int data = blocks[read_block_num].data[i];

        if (data == '\0') {
            null_found = true;
            break;
        }

        theCPU->memory->at(buffer_address) = data;
        if(TEST_DEBUG){std::cout<<(char)blocks[read_block_num].data[i];}
        buffer_address++;
        readed_count++;

    }
    int f = nth_read_block+1;
    int read_next_block = read_block_num + 1;
    //if file data contains more than one block, we need to read other blocks.
    while (readed_count < number_of_bytes && !null_found && files[the_file].alloc_blocks[f] == read_next_block) {
        read_block_num++;

        for(int i=0; i<BLOCK_SIZE && readed_count < number_of_bytes && readed_count<=files[the_file].size; ++i){

            int data = blocks[read_block_num].data[i];

            if (data == '\0') {
                null_found = true;
                break;
            }

            theCPU->memory->at(buffer_address) = data;
            if(TEST_DEBUG){std::cout<<(char)blocks[read_block_num].data[i];}
            buffer_address++;
            readed_count++;


        }
        f++;
        read_next_block++;

    }
    if(TEST_DEBUG){std::cout<<"Readed count:"<<readed_count<<"\n";}

    theCPU->memory->at(buffer_address++) = '\0';
    files[the_file].file_pointer+=readed_count;

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    sprintf (files[the_file].last_access_time, "%s.%09ld", buff, ts.tv_nsec);

    theCPU->state->b = (uint8_t) readed_count;

    return FREAD_CYCLE;
}

uint64_t GTUOS::handleFileSeek() {

    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: FSEEK"<<std::endl;}

    uint32_t address = (theCPU->state->b << 8) | theCPU->state->c;

    int num[5];
    memset(&num, 0, sizeof(num));
    int i =0;
    while(theCPU->memory->at(address) != '\0') {
        num[i] = theCPU->memory->at(address++) - 48;
        i++;
        if(i>5) break;
    }
    int seek_value = 0;

    for(int j=0; j<i; ++j)
        seek_value+=pow(10,i-1-j)*num[j];

//    std::string den(num);
//
//    seek_value = std::stoi(den);
//
//    seek_value = atoi(num);
//    sscanf(num, "%d", &seek_value);

    int handleID = theCPU->state->d;



    bool find_file = false;
    int the_file;
    i = 0;
    for (; i < open_files_table.size() && !find_file; ++i) {
        if (open_files_table[i]->fileID == handleID) {

            for(int j=0; j<file_count&& !find_file; ++j){
                if (files[j].fileID == handleID) {
                    the_file = j;
                    find_file = true;

                }
            }
        }
    }

    if (!find_file) {
        theCPU->state->b = (uint8_t) 0;
        return 0;
    }

    if(seek_value >= files[the_file].size)
        files[the_file].file_pointer = files[the_file].size;
    else
        files[the_file].file_pointer = seek_value;

    theCPU->state->b = (uint8_t) 1;

    return FSEEK_CYCLE;
}

uint64_t  GTUOS::handleDirRead() {

    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: DIRREAD"<<std::endl;}
    std::string temp;
    uint32_t address = (theCPU->state->b << 8) | theCPU->state->c;

    for (int i=0; i<file_count; ++i){


        theCPU->memory->at(address++) = 'N';
        theCPU->memory->at(address++) = 'a';
        theCPU->memory->at(address++) = 'm';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = ':';

        for(int j=0; j<100;++j){
            int data = files[i].filename[j];
            if(data == '\0')
                break;
            theCPU->memory->at(address++) = (char)data;

        }
        theCPU->memory->at(address++) = ',';


        theCPU->memory->at(address++) = 'S';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'z';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = ':';
        temp =  std::to_string(files[i].size);
        for(int m=0; m<temp.length(); ++m)
            theCPU->memory->at(address++) = temp[m];

        theCPU->memory->at(address++) = ',';

        theCPU->memory->at(address++) = 'C';
        theCPU->memory->at(address++) = 'r';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = 'a';
        theCPU->memory->at(address++) = 't';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'o';
        theCPU->memory->at(address++) = 'n';
        theCPU->memory->at(address++) = 'T';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'm';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = ':';
//        temp =  std::to_string(files[i].creation_time);
//        for(int m=0; m<temp.length(); ++m)
//            theCPU->memory->at(address++) = temp[m];

        for(int m=0; m<27; ++m)
            theCPU->memory->at(address++) = files[i].creation_time[m];

        theCPU->memory->at(address++) = ',';


        theCPU->memory->at(address++) = 'M';
        theCPU->memory->at(address++) = 'o';
        theCPU->memory->at(address++) = 'd';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'f';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'c';
        theCPU->memory->at(address++) = 'a';
        theCPU->memory->at(address++) = 't';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'o';
        theCPU->memory->at(address++) = 'n';
        theCPU->memory->at(address++) = 'T';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'm';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = ':';
//        temp =  std::to_string(files[i].last_modification_time);
//        for(int m=0; m<temp.length(); ++m)
//            theCPU->memory->at(address++) = temp[m];
        for(int m=0; m<27; ++m)
            theCPU->memory->at(address++) = files[i].last_modification_time[m];

        theCPU->memory->at(address++) = ',';


        theCPU->memory->at(address++) = 'A';
        theCPU->memory->at(address++) = 'c';
        theCPU->memory->at(address++) = 'c';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = 's';
        theCPU->memory->at(address++) = 's';
        theCPU->memory->at(address++) = 'T';
        theCPU->memory->at(address++) = 'i';
        theCPU->memory->at(address++) = 'm';
        theCPU->memory->at(address++) = 'e';
        theCPU->memory->at(address++) = ':';
//        temp =  std::to_string(files[i].last_access_time);
//        for(int m=0; m<temp.length(); ++m)
//            theCPU->memory->at(address++) = temp[m];
        for(int m=0; m<27; ++m)
            theCPU->memory->at(address++) = files[i].last_access_time[m];


        theCPU->memory->at(address++) = ',';





        theCPU->memory->at(address++) = 'F';
        theCPU->memory->at(address++) = 'p';
        theCPU->memory->at(address++) = 't';
        theCPU->memory->at(address++) = 'r';
        theCPU->memory->at(address++) = ':';
        temp =  std::to_string(files[i].file_pointer);
        for(int m=0; m<temp.length(); ++m)
            theCPU->memory->at(address++) = temp[m];

        theCPU->memory->at(address++) = ',';

        theCPU->memory->at(address++) = 'D';
        theCPU->memory->at(address++) = 'a';
        theCPU->memory->at(address++) = 't';
        theCPU->memory->at(address++) = 'a';
        theCPU->memory->at(address++) = ':';

        bool fend = false;
        for(int k=0; k<files[i].alloc_block_num && !fend; ++k){

            for(int m=0; m<BLOCK_SIZE && !fend; ++m) {

                int data_ =  blocks[files[i].alloc_blocks[k]].data[m];
                if(data_ == '\0') {
                    fend = true;break;
                }
                theCPU->memory->at(address++) = data_;



            }
        }

        theCPU->memory->at(address++) = '\n';
        theCPU->memory->at(address++) = '\n';

    }
    theCPU->memory->at(address++) = '\0';


    return DIRREAD_CYCLE;
}

int  GTUOS::compaction(int block_num){

    if(blocks[4095].is_in_use == 1) //memory full
        return -1;

    //cary blocks
    std::set<int> carryed_files;
    int i = BLOCK_CAP-1;
    for(; i!=block_num+1; --i){

        blocks[i] = blocks[i-1];
        blocks[i].block_num = i;
        carryed_files.insert(blocks[i-1].owner);

    }
    for(auto it = carryed_files.begin(); it != carryed_files.end(); ++it){
        if(*it != -1){
            for(int i=0; i< files[*it].alloc_block_num; ++i){
                files[*it].alloc_blocks[i] = files[*it].alloc_blocks[i] +1;
            }
        }
    }
    memset(&blocks[block_num+1], 0, sizeof(blocks[block_num+1]));
    blocks[block_num+1].block_num = block_num+1;

    return block_num+1;
}

int GTUOS::alloc_new_block(int file_num){

    int the_files_block_size = files[file_num].alloc_block_num;

    int last_block_num = files[file_num].alloc_blocks[the_files_block_size-1];

    //if next block is empty, append next block
    if(blocks[last_block_num+1].is_in_use == 0){
        blocks[last_block_num+1].is_in_use = 1;
        blocks[last_block_num+1].owner = file_num;
        //files[file_num].blocks.push_back(last_block_num+1);
        files[file_num].alloc_blocks[ files[file_num].alloc_block_num ] = last_block_num+1;
        files[file_num].alloc_block_num++;
        return last_block_num+1;
    }
    else{ //next block is not empty

        int block_to_write =  compaction(last_block_num);
        if(block_to_write == -1)
            return -1;
        blocks[block_to_write].is_in_use = 1;
        blocks[block_to_write].owner = file_num;

        //files[file_num].blocks.push_back(block_to_write);

        files[file_num].alloc_blocks[ files[file_num].alloc_block_num ] = block_to_write;
        files[file_num].alloc_block_num++;

        return block_to_write;


    }





}





uint64_t GTUOS::handleTCreate(uint64_t *cycle){

    //thread tablenın boş olan elemanına atamalar yapılır, ready ve address ataması.
    //schedular queue ya ko


    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TCREATE"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    int created_thread_tid = scheduler.add_new_thread((uint16_t) address,*cycle_count);
    if (created_thread_tid != -1){
        theCPU->state->b = (uint8_t ) created_thread_tid;
        context_switch_happen = scheduler.schele(theCPU,1);
        *cycle = 0; //context switch oldu cycle = 0

    }
    else
        theCPU->state->b = 0;


    return TCREATE_CYCLE;
}
uint64_t GTUOS::handleTExit(uint64_t *cycle){
    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TExit"<<std::endl;

    int exit_status = scheduler.exit_thread();
    theCPU->state->b = (uint8_t ) exit_status;

    if (exit_status == 1){ //if exit is successed.
        context_switch_happen = scheduler.schele(theCPU,1);
        *cycle = 0; //context switch oldu cycle = 0
    }

    return TEXIT_CYCLE;
}
/* Register B holds the thread ID of the thread to wait for.*/
uint64_t GTUOS::handleTJoin(uint64_t *cycle){

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TJoin"<<std::endl;

    uint8_t waiting_tid = theCPU->state->b;

    scheduler.tjoin(waiting_tid);
    context_switch_happen = scheduler.schele(theCPU,1);
    *cycle = 0; //context switch oldu cycle = 0


    return TJOIN_CYCLE;
}
uint64_t GTUOS::handleTYield(uint64_t *cycle){

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TYield"<<std::endl;

    context_switch_happen = scheduler.schele(theCPU,1);
    *cycle = 0; //context switch oldu cycle = 0

    return TYIELD_CYCLE;
}

void GTUOS::timer_interrupt(uint64_t *cycle){
    if (scheduler.round_robin_queue.size()> 1) {
        if (*cycle / scheduler.quantum_time > 0) {
            *cycle = 0;
            //std::cout<<"Timer interrupt"<<std::endl;

            context_switch_happen = scheduler.schele(theCPU, 0);

        }
    }
}



uint64_t GTUOS::handlePrintB()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_B"<<std::endl;
    std::cout<<"Content of RegisterB:" <<(int)theCPU->state->b<<std::endl;
    return PRINT_B_CYCLE;
}

uint64_t GTUOS::handlePrintMem()const{
    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_MEM"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    std::cout<<"BC adress is:"<<(uint32_t)address<<std::endl;
    std::cout<<"BC content is:"<<(int)(theCPU->memory->at(address))<<std::endl;

    return PRINT_MEM_CYCLE;
}
//Reads an integer from the keyboard and puts it in register B.
uint64_t GTUOS::handleReadB()const{
    std::cout<<"System Call Handle: READ_B"<<std::endl;

    int value;
    std::cout<<"Enter an integer between 0 to 255 for register B:";

    std::cin >> value;


    if (value <0 || value>255){
        std::cout<<"The number is not between 0 to 255. OS chose 0 for registerB.";
        theCPU->state->b = 0;
    }
    else
        theCPU->state->b = (uint8_t) value;

    return READ_B_CYCLE;

}

uint64_t GTUOS::handleReadMem()const{

    std::cout<<"System Call Handle: READ_MEM"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    int value;
    std::cout<<"Enter an integer between 0 to 255 for memory address of BC:";
    std::cin >> value;

    if (value <0 || value>255){
        std::cout<<"The number is not between 0 to 255. OS chose 0.";
        theCPU->memory->at(address) = 0;
        std::cout<<"The 0 is assigned to the memory address of:" << (unsigned)address<<std::endl;

    }
    else{
        theCPU->memory->at(address) = (uint8_t )  value;
        std::cout<<"The "<<value<<" is assigned to the memory address of:" << (unsigned)address<<std::endl;
    }

    return READ_MEM_CYCLE;

}
// Prints the null terminated string at the memory location pointed by B and C ?????????
uint64_t GTUOS::handlePrintStr()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_STR"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;
    //std::cout<<"The address of "<<(int)address;

    bool Flag = true;
    std::string content = "";
    while (Flag)
        if (theCPU->memory->at(address) == '\0')
            Flag = false;
        else
            content+= theCPU->memory->at(address++);
    //std::cout<<" content is :";
    std::cout<<content<<"\n";


    return PRINT_STR_CYCLE;
}
//Reads the null terminated string from the keyboard and puts the result at the memory location pointed by B and C
uint64_t GTUOS::handleReadStr()const{

    if(TEST_DEBUG){std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: READ_STR"<<std::endl;}

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    uint32_t input_writed_address = address;

    std::cout<<"Enter a string: ";
    std::string input = "";
    //std::cin.ignore();
    getline(std::cin,input);
    if (input == "\n" || input == "") //for buffer.
        getline(std::cin,input);

    input += "\0";

    for (unsigned int i=0; i<input.length(); ++i)
        theCPU->memory->at(address++) = input[i];

    theCPU->memory->at(address) = '\0';

    if(TEST_DEBUG){std::cout<<"The string:"<<input<<" writed to memory address is:"<<input_writed_address<<std::endl;}

    return READ_STR_CYCLE;
}
//Produces a random byte and puts in register B
uint64_t GTUOS::handleGetRnd()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: GET_RND"<<std::endl;

    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);

    std::uniform_int_distribution<> dist{0,256};
    int random_byte = dist(eng);

    theCPU->state->b = random_byte;

    std::cout<<"Random number:"<<random_byte<<" produced and saved to registerB"<<std::endl;


    return GET_RND_CYCLE;
}

void GTUOS::saveMemory(const CPU8080 & cpu, std::string filename)const{
    std::fstream myfile;
    myfile.open(filename,std::fstream::out);

    for (int i=0; i<0x1000; ++i){
        char str[10];
        sprintf(str,"0x%08x ",i*16);

        std::string temp(str);

        for (int j=0; j<0x10; ++j){
            sprintf(str,"0x%02x ",cpu.memory->at(i*16+j));
            temp += str;
        }

        myfile << temp <<"\n";

    }

    myfile.close();

}

void GTUOS::calculatePC(int mode) {

    if(mode == 0){
        oscallpc = theCPU->state->pc;
    }
    else{
        if (theCPU->state->pc == 3){
            //running threade kaydet os_called_from yi
            scheduler.save_called_os_pc(oscallpc);

        }
    }

}

void GTUOS::setContext_switch_happen(bool context_switch_happen) {
    GTUOS::context_switch_happen = context_switch_happen;
}



GTUOS::Scheduler::Scheduler(const CPU8080* cpu8080,uint64_t *cycle_count,const uint64_t quantum, int debug) {
    quantum_time = quantum;
    Scheduler::DEBUG = debug;
    Scheduler::cycle_count = cycle_count;
    for(int i=0; i<THREAD_NUM; ++i){
        thread_table[i].setThread_id(i);
        thread_table[i].setAvailable(0);
        thread_table[i].setCycle(0);
        thread_table[i].waiting_tid = -1;

        //bzero(&thread_table[i].registers, sizeof(State8080));
    }
    thread_table[0].setState(RUNNING);
    thread_table[0].setAddress(0x0000);
    thread_table[0].setStarting_cycle(*cycle_count);
    thread_table[0].setStack_space(STACK_SPACE);
    thread_table[0].setAvailable(1);
    thread_table[0].setRegisters(*(cpu8080->state));


    Running_Thread_ID = 0;
    round_robin_queue.push(&(thread_table[0]));
//    round_robin_queue.push(std::make_shared<ThreadInformation>(thread_table[0]));

    last_time = 0;
}


int GTUOS::Scheduler::add_new_thread(uint16_t pc, uint64_t cycle_count) {

    bool find_avaible_thread = false;
    int i;
    for(i=0; (i<THREAD_NUM && !find_avaible_thread);  i+=1)
        if(thread_table[i].getAvailable() == 0)
            find_avaible_thread = true;

    i-=1;
    //bzero(&(thread_table[i].registers), sizeof(State8080));


    thread_table[i].setState(READY);
    thread_table[i].setRegisterPC(pc);
    thread_table[i].setAddress(pc);
    thread_table[i].setStarting_cycle(cycle_count);
    thread_table[i].setStack_space(STACK_SPACE);  ///////////
    thread_table[i].setAvailable(1);

    round_robin_queue.push(&(thread_table[i]));
//    round_robin_queue.push(std::make_shared<ThreadInformation>(thread_table[i]));

    if (find_avaible_thread)
        return i;
    else
        return -1;

}

int GTUOS::Scheduler::exit_thread() {

    if (thread_table[Running_Thread_ID].getAvailable() == 1 && thread_table[Running_Thread_ID].getState() == RUNNING){

        thread_table[Running_Thread_ID].setState(READY); //Running kalmamalı state
        thread_table[Running_Thread_ID].setAvailable(0); //threadi kullanılmıyor olarak işaretlemeliyiz
        interrupt_handler(Running_Thread_ID);
        return 1;
    } else
        return 0;

}

void GTUOS::Scheduler::interrupt_handler(uint8_t exit_thread_id){

    int i;
    for(i=0; i<THREAD_NUM; ++i){
        // eger ölen thread'i bekleyen birisi varsa block'ed den ready'e taşınmalı.
        // int16_t olan tipi -1 koyabilmek icin yapildi, -1 degilse karsılastırmak ıcın cast edılıyor.
        if( thread_table[i].waiting_tid != -1 and (uint8_t) thread_table[i].waiting_tid == exit_thread_id) {
            thread_table[i].waiting_tid = -1;
            thread_table[i].setState(READY);

        }
    }

    /*
    for(i=0; i<THREAD_NUM; ++i){
        // eger ölen thread'i bekleyen birisi varsa block'ed den ready'e taşınmalı.
        if(std::find(thread_table[i].waiting_tids.begin(), thread_table[i].waiting_tids.end(), exit_thread_id) != thread_table[i].waiting_tids.end() )
            thread_table[i].waiting_tids.erase(std::remove(thread_table[i].waiting_tids.begin(),thread_table[i].waiting_tids.end(),exit_thread_id)); //remove

        if(thread_table[i].waiting_tids.empty())
            thread_table[i].setState(READY);

    }*/
}

void GTUOS::Scheduler::copyRegisters(State8080 registers){

    uint16_t copy_pc = thread_table[Running_Thread_ID].registers.pc;
    thread_table[Running_Thread_ID].registers = registers;
    thread_table[Running_Thread_ID].registers.pc = copy_pc;

}
//Schele ' e thread gelmeden önce PC'si ayarlanmalı!
bool GTUOS::Scheduler::schele(CPU8080 *CPU8080, int os_call) {

    uint8_t first_running_tid = Running_Thread_ID;
    uint64_t total_cycle_of_old_thread = thread_table[Running_Thread_ID].getCycle();

    //current thread blocklanmadıysa, runningden ready e getir.
    //thread_table[Running_Thread_ID].registers = *(CPU8080->state);

    if(thread_table[Running_Thread_ID].registers.pc == 12 ){
        std::cout<<(int)Running_Thread_ID<<" aaaaaa:"<<thread_table[Running_Thread_ID].getOs_called_pc()<<std::endl;

        thread_table[Running_Thread_ID].registers.pc = thread_table[Running_Thread_ID].getOs_called_pc();
    }
    else if (os_call == 1)
        copyRegisters( *(CPU8080->state));
    else //timer interrupt
        thread_table[Running_Thread_ID].registers = *(CPU8080->state);


    if ( thread_table[Running_Thread_ID].getState() !=BLOCKED )
        thread_table[Running_Thread_ID].setState(READY);
    //Running threaddeki degerleri güncelle.

    if(thread_table[Running_Thread_ID].getAvailable() == 1) { //Running thread isini bitirmediyse tekrar queue ye eklenemi
        round_robin_queue.push(&(thread_table[Running_Thread_ID]));

    }

    update_thread_cycle(Running_Thread_ID,*cycle_count - last_time);
    last_time = *cycle_count;


    round_robin_queue.pop(); //Running thread queueden çıkartılır.


    while( round_robin_queue.front()->getState() == BLOCKED || round_robin_queue.front()->getAvailable()==0 ){     // QUEUEDEN CIKAN THREAD BLOCKED ISE
        round_robin_queue.push(round_robin_queue.front());
        round_robin_queue.pop(); //Running thread queueden çıkartılır.
//        std::cout<<"OS CRASH, ALL THREADS ARE BLOCKED"<<std::endl;

    }
    round_robin_queue.front()->setState(RUNNING);
    Running_Thread_ID = round_robin_queue.front()->getThread_id();
    //*(CPU8080->state) = round_robin_queue.front()->registers;
    //CPU8080->state = (State8080*) calloc(1,sizeof(State8080));

    CPU8080->state = &(round_robin_queue.front()->registers);
    //*(CPU8080->state) = round_robin_queue.front()->registers;


    if (first_running_tid != Running_Thread_ID) { //threat switch happened.
        if (DEBUG == 2){
            std::cout<<"threat switch happened, TID: "<<(int)first_running_tid<<" to TID: "<<(int)Running_Thread_ID<<std::endl;
            std::cout<<"The total cycles spent for the blocked thread: "<<total_cycle_of_old_thread<<std::endl;
        }
        else if(DEBUG == 3){
            print_thread_information();
        }
        return true;
    }
    else
        return false;
}
void GTUOS::Scheduler::print_thread_information(){
    std::cout<<"TID \t StckCycle\t RunCycle \t State \t StckAdres \t StckSpace \tA   B   C   D   E   H   L    SP"<<std::endl;

    int i;
    for(i=0; i<THREAD_NUM ;  i++)
        if(thread_table[i].getAvailable() == 1){
            printf("%04d \t %04d \t\t %04d \t\t %04d \t %04d \t\t %04d \t\t", (int)thread_table[i].getThread_id(), (int)thread_table[i].getStarting_cycle(), (int)thread_table[i].getCycle(),
                   (int)thread_table[i].getState(), (int)thread_table[i].getAddress(),(int)thread_table[i].getStack_space());
            print_registers(thread_table[i].getRegisters());

        }
}

void GTUOS::Scheduler::print_registers(State8080 registers){
    printf("$%02x $%02x $%02x $%02x $%02x $%02x $%02x  %04x\n", registers.a, registers.b, registers.c,
           registers.d, registers.e,registers.h, registers.l, registers.sp);

}


void GTUOS::Scheduler::update_pc(const uint16_t pc,const uint64_t cycle_count) {

    thread_table[Running_Thread_ID].registers.pc = pc;
    uint64_t cycle_run= cycle_count - thread_table[Running_Thread_ID].getStarting_cycle();
    //thread_table[Running_Thread_ID].setCycle(cycle_run);

}


int GTUOS::Scheduler::getRunning_Thread_ID() const {
    return Running_Thread_ID;
}

void GTUOS::Scheduler::setRunning_Thread_ID(uint8_t Running_Thread_ID) {
    Scheduler::Running_Thread_ID = Running_Thread_ID;
}

uint64_t GTUOS::Scheduler::getQuantum_time() const {
    return quantum_time;
}

void GTUOS::Scheduler::save_called_os_pc(uint16_t os_called_pc) {
    thread_table[Running_Thread_ID].setOs_called_pc(os_called_pc);
}
uint16_t GTUOS::Scheduler::get_called_os_pc(){
    return thread_table[Running_Thread_ID].getOs_called_pc();
}
void GTUOS::Scheduler::tjoin(const uint8_t waiting_tid){

    //thread_table[Running_Thread_ID].waiting_tids.push_back(waiting_tid); //beklediği thread id yazılır

    //beklenimek istenen thread çoktan ölmüş olabilir.
    if (thread_table[waiting_tid].getAvailable() == 1){
        thread_table[Running_Thread_ID].waiting_tid = waiting_tid;          //Bekledigi thread id yazılır
        thread_table[Running_Thread_ID].setState(BLOCKED);                  //BLOCK the running thread.
    }

}
