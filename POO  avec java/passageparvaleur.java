public class PassTest {
    public void changePrimitive(int value){
        ++value;
    }

    public void changeReference(MyDate from, MyDate to){
        from = to;
    }

    public void changeObjectDay(MyDate date, int day){
        date.setDay(day);
    }
}

PassTest pt = new PassTest();
int x = 100;
System.out.println( x ); //resultat 100
MyDate oneDate = new MyDate(3,10,2050); 
MyDate anotherDate = new MyDate(3,10,2020);
pt.changeReference( oneDate, anotherDate );
Systeme.out.println( onDate.getYear() ); //resultat 2050




