#include "csapp.h"
char buffer[256];
/**
 * @brief displays the file/directory 
 * 
 * @param path path of the file/directory 
 * @param name name of the file/directory
 */
void print_stat(string path,string name)
{
    struct stat entity;
    strcpy(buffer,path.c_str());
    if(stat(buffer,&entity)==-1)
    {
        perror("error loading metadata");
        exit(EXIT_FAILURE);
    }
    auto flag=entity.st_mode;
    printf((S_ISDIR(flag))? "d":"-");
    printf((flag& S_IRUSR)? "r":"-");
    printf((flag & S_IWUSR)? "w":"-");
    printf((flag & S_IXUSR)? "x":"-");
    printf((flag & S_IRGRP)? "r":"-");
    printf((flag & S_IWGRP)? "w":"-");
    printf((flag & S_IXGRP)? "x":"-");
    printf((flag & S_IROTH)? "r":"-");
    printf((flag & S_IWOTH)? "w":"-");
    printf((flag & S_IXOTH)? "x":"-");
    cout<<" | "<<name<<endl;
}
void seperator()
{
    cout<<"------------------------------------------------------"<<endl;
}
/**
 * @brief A DFS-recursive approach to printing the directories and files under it.
 * 
 * @param path the path of the directory
 */
bool search(string path,string target)
{
    bool flag=false;
    DIR* dir_stream=opendir(path.c_str());
    //if no more directory stream then just return
    if(dir_stream==NULL)
    {
        return false;
    }
    struct dirent* entity=readdir(dir_stream);
    while(entity!=NULL)
    {
        if(string(entity->d_name) == target)
        {
            closedir(dir_stream);
            return true;
        }
        string new_path=path;
        new_path.append("/");
        new_path.append(string(entity->d_name));
        if(entity->d_type == DT_DIR && strcmp(entity->d_name,".")!=0 && strcmp(entity->d_name,"..")!=0)
        {
            flag= flag || search(new_path,target);
            if(flag)
            {
                closedir(dir_stream);
                return flag;   
            }
        }
        entity=readdir(dir_stream);
    }
    closedir(dir_stream);
    return false;
}
void fun()
{
    cout<<"bye bye";
}
int main()
{
    atexit(fun);
    cout<<"hello"<<endl;
    return 0;   
}