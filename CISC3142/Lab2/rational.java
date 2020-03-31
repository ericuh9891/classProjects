class Rational{
    private int numer;
    private int denom;
    Rational(int numer, int denom)throws RationalException{
            if(denom == 0){
                throw new RationalException("Denominator cannot be zero");
            }
            int gcd = gcd(numer,denom);
            this.numer = numer/gcd;
            this.denom = denom/gcd;
    }
    Rational(int numer){
        this.numer = numer;
        denom = 1;
    }
    Rational(){
        numer = 0;
        denom = 1;
    }
    Rational(Rational rational){
        
            this.numer = rational.getNumerator();
            if(rational.getDenominator() == 0){
                throw new RationalException("Denominator cannot be zero");
            }
            else
                this.denom = rational.getDenominator();
    }
    public int getNumerator(){
        return this.numer;
    }
    public int getDenominator(){
        return this.denom;
    }
    public Rational negate(){
        return new Rational(numer * -1,denom);
    }
    public Rational inverse(){
        return new Rational(denom,numer);
    }
    public Rational add(Rational rational){
        int newNumer = this.numer * rational.getDenominator() + rational.getNumerator() * this.denom;
        int newDenom = this.denom * rational.getDenominator();
        return new Rational(newNumer,newDenom);
    }
    public Rational sub(Rational rational){
        int newNumer = this.numer * rational.getDenominator() - rational.getNumerator() * this.denom;
        int newDenom = this.denom * rational.getDenominator();
        return new Rational(newNumer,newDenom);
    }
    public Rational mul(Rational rational){
        return new Rational(this.numer * rational.getNumerator(),this.denom * rational.getDenominator());
    }
    public Rational div(Rational rational){
        return new Rational(this.numer * rational.getDenominator(), this.denom * rational.getNumerator());
    }
    public void addInPlace(Rational rational){
        this.numer = this.numer * rational.getDenominator() + rational.getNumerator() * this.denom;
        this.denom = this.denom * rational.getDenominator();
        int gcd = gcd(this.numer,this.denom);
        this.numer = this.numer/gcd;
        this.denom = this.denom/gcd;
    }
    public void subInPlace(Rational rational){
        this.numer = this.numer * rational.getDenominator() - rational.getNumerator() * this.denom;
        this.denom = this.denom * rational.getDenominator();
        int gcd = gcd(this.numer,this.denom);
        this.numer = this.numer/gcd;
        this.denom = this.denom/gcd;
    }
    public void mulInPlace(Rational rational){
        this.numer = this.numer * rational.getNumerator();
        this.denom = this.denom * rational.getDenominator();
        int gcd = gcd(this.numer,this.denom);
        this.numer = this.numer/gcd;
        this.denom = this.denom/gcd;    
    }
    public void divInPlace(Rational rational){
        this.numer = this.numer * rational.getDenominator();
        this.denom = this.denom * rational.getNumerator();
        int gcd = gcd(this.numer,this.denom);
        this.numer = this.numer/gcd;
        this.denom = this.denom/gcd;    
    }
    private int gcd(int num1, int num2){
        if(num2 == 0)
            return num1;
        else return gcd(num2, num1%num2);
    }
    public int compareTo(Rational rational){
        int tempCallerNumer = this.numer * rational.getDenominator();
        int tempArgNumer = rational.getNumerator() * this.denom;
        if(tempCallerNumer < tempArgNumer)
            return -1;
        else if(tempCallerNumer > tempArgNumer)
            return 1;
        else return 0;
    }
    public boolean equals(Rational rational){
        if(this.compareTo(rational) == 0)
            return true;
        else return false;
    }
@Override
    public String toString(){
        if(this.denom == 0 || this.denom == 1)
            return this.numer + "";
        else return this.numer + "/" + this.denom;
    }   
}
