void cachetest()
{
    LRU cache(3);
    cache.set(1,1);
    cache.set(2,2);
    cache.set(3,3);
    cache.set(4,4);
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<"--------------------"<<endl;
    cache.set(2,5);
    cout<<cache.get(2)<<endl;
    cache.set(5,5);
    cout<<cache.get(2)<<endl;

}