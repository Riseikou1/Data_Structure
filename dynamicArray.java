package Structure;
public class Dynamic_Arrays {
    int size;
    int capacity=10;
    Object[] array;
    public Dynamic_Arrays(){
        this.array = new Object[capacity];
    }
    public Dynamic_Arrays(int capacity) {
        this.capacity = capacity;
        this.array = new Object[capacity];
    }
    public void add(Object data) {
        if(size >= capacity) {
            grow();
        }
        array[size] = data;
        size ++ ;
    }
    public void insert(int index, Object data){
        if(size >= capacity) {
            grow();
        }
        for(int i=size;i>index;i--){
            array[i] = array[i-1];
        }
        array[index] = data;
        size ++ ;
    }
    public void delete(Object data){
        for(int i=0;i<size;i++){
            if(array[i] == data) {
                for(int j=0;j<(size-i-1);j++){
                    array[i+j] = array[i+j+1];
                }
                array[size-1] = null;
                size -- ;
                if(size <= (int)capacity/2){
                    shrink();
                }
                break;
            }
        }
    }
    public int search(Object data){
        for(int i=0;i<size;i++){
            if(array[i] == data){
                return i;
            } 
        }
        return -1;
    }   
    public void grow(){
        int newCapacity = capacity*2;
        Object[] newArray = new Object[newCapacity];
        for(int i=0;i<size;i++){
            newArray[i] = array[i];
        }
        capacity = newCapacity;
        array = newArray;
    }
    public void shrink(){
        int newCapacity = capacity/2;
        Object[] newArray = new Object[newCapacity];
        for(int i=0;i<size;i++){
            newArray[i] = array[i];
        }
        capacity = newCapacity;
        array = newArray;
    }
    public boolean isEmpty(){
        return size == 0;
    }
    public String toString() {
        String string = "";
        for(int i=0;i<capacity;i++){
            string += array[i] + ", ";
        }
        if(string !=""){
            string = "["+ string.substring(0,string.length()-2)+"]"; // -2 gej suuliin elementnii ardah baigaa taslal, bolon space-iig zailuulj baigaa.
        }
        else {
            string = "[]";
        }
        return string ;
    }
    public static void main(String[] args) {
        Dynamic_Arrays dynamicArray = new Dynamic_Arrays(6);
        dynamicArray.add("A");
        dynamicArray.add("B");
        dynamicArray.add("C");
        dynamicArray.add("D");
        dynamicArray.add("E");
        dynamicArray.add("F");
        dynamicArray.insert(0,"Temuujin");
        System.out.println("capacity: "+dynamicArray.capacity);
        dynamicArray.delete("A");
        dynamicArray.delete("B");
        dynamicArray.delete("C");
        dynamicArray.delete("D");
        dynamicArray.delete("E");
        System.out.println("index of your shit: "+ dynamicArray.search("C"));
        System.out.println("size: "+dynamicArray.size);
        System.out.println("capacity: "+dynamicArray.capacity);
        System.out.println(dynamicArray); // zaaval toString gej duudah heregguigeer bas bolno.
    }
}
