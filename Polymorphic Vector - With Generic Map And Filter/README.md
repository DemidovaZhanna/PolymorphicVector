So the difference between two folders (implementations) is that here first of all Map changes initial Vector, second of all I don't need to use in third party programs functions MapI, MapC, FilterI, FilterC and only define them and use them only in generic Map and Filter, thirdly I had to change all function's signatures that was previously used in MapI, MapC, FilterI, FilterC.

That's pretty much sums it up. 

I don't know which one is better because in this case I have generic functions and it is really cool but they (Map) change initial Vector which I don't really like. In another implementation I don't have generic Map and Filter but at least they don't change original Vector. 
