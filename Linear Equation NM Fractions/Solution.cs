namespace LinearSystems {
    using System;
    using System.Collections.Generic;
    using System.Numerics;

    public class Fraction{
        public BigInteger numerator;
        public BigInteger denominator;

        public Fraction(BigInteger numerator){
            this.numerator = numerator;
            denominator = 1;
            Simplify();
        }
        public Fraction(BigInteger numerator, BigInteger denominator){
            if (denominator == 0) throw new ArgumentException("Denominator cannot be zero.", nameof(denominator));
            this.numerator = numerator;
            this.denominator = denominator;
            Simplify();
        }
        public Fraction(string s){
            string[] sp = s.Split('/');
            numerator = new BigInteger(int.Parse(sp[0]));
            if (sp.Length > 1){
                denominator = new BigInteger(int.Parse(sp[1]));
            }
            else{
                denominator = new BigInteger(1);
            }
            Simplify();
        }

        public void Simplify(){
            BigInteger div = GCD(numerator, denominator);
            numerator /= div;
            denominator /= div;
            if (denominator < 0){
                denominator *= -1;
                numerator *= -1;
            }
        }
        
        public static BigInteger Comparator(Fraction a, Fraction b) => a.numerator * b.denominator - a.denominator * b.numerator;
        public static Fraction operator +(Fraction a, Fraction b)
            => new Fraction(a.numerator * b.denominator + b.numerator * a.denominator, a.denominator * b.denominator);
        public static Fraction operator -(Fraction a, Fraction b)
            => new Fraction(a.numerator * b.denominator - b.numerator * a.denominator, a.denominator * b.denominator);
        public static Fraction operator -(Fraction a) => new Fraction(-a.numerator, a.denominator);
        public static Fraction operator *(Fraction a, Fraction b) => new Fraction(a.numerator * b.numerator, a.denominator * b.denominator);
        public static Fraction operator /(Fraction a, Fraction b){
            if (b.numerator == 0) throw new DivideByZeroException();
            return new Fraction(a.numerator * b.denominator, a.denominator * b.numerator);
        }
        public override string ToString() => denominator==1 ? $"{numerator}" : $"{numerator} / {denominator}";
        
        public static BigInteger GCD(BigInteger a, BigInteger b){
            if (a==0) return b;
            return GCD(b%a, a);
        }
    }

    public class Vector{
        public List<Fraction> v;
        public Vector(){
            v = new List<Fraction>();
        }
        public Vector(int dim){
            v = new List<Fraction>();
            for (int i = 0; i < dim; i++){
                v.Add(new Fraction(new BigInteger(0)));
            }
        }

        public override string ToString()
        {
            string ret = "(";
            for (int i = 0; i < v.Count-1; i++){
                ret += v[i].ToString() + "; ";
            }
            ret += v[v.Count-1].ToString() + ") ";
            return ret;
        }
    }

    public class Equation{
        public List<Fraction> row;
        
        public Equation(){
            row = new List<Fraction>();
        }

        public bool IsZero(){
            for (int i = 0; i < row.Count; i++){
                if (row[i].numerator != 0) return false;
            }
            return true;
        }

        public static Equation operator *(Equation e, Fraction f){
            Equation ret = new Equation();
            for (int i = 0; i < e.row.Count; i++){
                ret.row.Add(e.row[i] * f);
            }
            return ret;
        }
        public static Equation operator /(Equation e, Fraction f){
            Equation ret = new Equation();
            for (int i = 0; i < e.row.Count; i++){
                ret.row.Add(e.row[i] / f);
            }
            return ret;
        }
        public static Equation operator -(Equation a, Equation b){
            if (a.row.Count != b.row.Count) throw new Exception("Equations have different lengths");
            Equation ret = new Equation();
            for (int i = 0; i < a.row.Count; i++){
                ret.row.Add(a.row[i] - b.row[i]);
            }
            return ret;
        }

        public override string ToString()
        {
            string ret = "";
            int i = 0;
            while (i < row.Count - 2){
                ret += $"{row[i].ToString()} x{i} + ";
                i++;
            }
            while (i < row.Count - 1){
                ret += $"{row[i].ToString()} x{i} = ";
                i++;
            }
            ret += $"{row[i].ToString()}";
            return ret;
        }
    }

    public class LinearSystem
    {
        public List<Equation> system = new List<Equation>();
        public List<int> pivots = new List<int>();
        public int dim, dimImage, dimKernel;
        public List<Vector> solution;
        public List<int> insertedRows;
        public string Solve (string input)
        {
            system.Clear();
            string[] rows = input.Split('\n');
            foreach (string row in rows){
                string[] elements = row.Split(' ');
                Equation e = new Equation();
                foreach (string el in elements){
                    Fraction f = new Fraction(el);
                    e.row.Add(f);
                }
                system.Add(e);
            }

            dim = system[0].row.Count-1;

            Console.WriteLine(ToString());
            GaussianTriangulate();
            Console.WriteLine(ToString());
            TrimExcess();
            if (!CheckValid()) return "SOL=NONE";
            Console.WriteLine(ToString());
            CountDimensions();
            AddHyperParameters();
            Console.WriteLine(ToString());
            CreateSolutionVectors();
            PrintSolution();
            string result = CreateSolutionString();
            Console.WriteLine(result);
            return result;
        }

        private void PrintSolution(){
            for (int i = 0; i < solution.Count; i++){
                Console.WriteLine(solution[i].ToString());
            }
        }

        private string CreateSolutionString(){
            string ret = "SOL = ";
            ret += solution[0].ToString();
            for (int i = 1; i < solution.Count; i++){
                ret += $" + q{i} * " + solution[i].ToString();
            }
            return ret;
        }

        private Vector CreateSolutionVector(int column){
            Vector newVec = new Vector(dim);
            for (int j = 0; j < dim; j++){
                newVec.v[j] = system[j].row[column];
            }
            return newVec;
        }

        private void CreateSolutionVectors(){
            // there are dim kernel + 1 solution vectors
            solution = new List<Vector>();
            solution.Add(CreateSolutionVector(dim));
            foreach (int i in insertedRows){
                solution.Add(CreateSolutionVector(i));
            }
        }

        private void CountDimensions(){
            dimImage = system.Count;
            dimKernel = dim - dimImage;
            Console.WriteLine($"Phase space dim{dim}, image dim{dimImage}, kernel dim{dimKernel}");
        }

        private bool CheckValid(){
            for (int i = 0; i < system.Count; i++){
                bool lhsZero = true;
                for (int j = 0; j < system[i].row.Count-1; j++){
                    if (system[i].row[j].numerator != 0){
                        lhsZero = false;
                        break;
                    }
                }

                if (lhsZero && system[i].row[ system[i].row.Count-1 ].numerator != 0) return false;
            }
            return true;
        }

        private void GaussianTriangulate(){
            pivots.Clear();
            int h = 0, k = 0;

            while (h < system.Count && k < system[0].row.Count){
                // find k-th pivot
                int i_pivot = -1;
                for (int i = h; i < system.Count; i++){
                    if (system[i].row[k].numerator != 0){
                        i_pivot = i; break;
                    }
                }

                if (i_pivot == -1){
                    // No pivot
                    k++;
                }
                else{
                    system.Swap(i_pivot, h);
                    for (int i = h+1; i < system.Count; i++){
                        Fraction f = system[i].row[k] / system[h].row[k];
                        system[i] -= system[h] * f;
                    }
                    h++; k++;
                }
                //Console.WriteLine(ToString());
            }
            
            h = 0; k = 0;
            while (h < system.Count && k < system[0].row.Count){
                // find k-th pivot
                int i_pivot = -1;
                for (int i = h; i < system.Count; i++){
                    if (system[i].row[k].numerator != 0){
                        i_pivot = i; break;
                    }
                }

                if (i_pivot == -1){
                    // No pivot
                    k++;
                }
                else{
                    system[h] /= system[h].row[k];
                    h++; k++;
                }
                //Console.WriteLine(ToString());
            }
            
            h = 0; k = 0;
            while (h < system.Count && k < system[0].row.Count){
                // find k-th pivot
                int i_pivot = -1;
                for (int i = h; i < system.Count; i++){
                    if (system[i].row[k].numerator != 0){
                        i_pivot = i; break;
                    }
                }

                if (i_pivot == -1){
                    // No pivot
                    k++;
                }
                else{
                    //Console.WriteLine($"Pivot at {h}, {k}");
                    for (int i = h-1; i >= 0; i--){
                        Fraction f = system[i].row[k] / system[h].row[k];
                        system[i] -= system[h] * f;
                    }
                    h++; k++;
                }
                //Console.WriteLine(ToString());
            }//*/
        }
        
        private void AddHyperParameters(){
            insertedRows = new List<int>();
            for (int i = 0; i < dim; i++){
                //Console.WriteLine($"i = {i}, count = {system.Count}");
                if (system.Count <= i || system[i].row[i].numerator == 0){
                    // Add extra row
                    system.Insert(i, new Equation());
                    insertedRows.Add(i);
                    for (int j = 0; j <= dim; j++){
                        system[i].row.Add(new Fraction(0));
                    }
                    system[i].row[i].numerator = -1;
                }
            }
        }

        private void TrimExcess(){
            for (int i = system.Count-1; i >= 0; i--){
                if (system[i].IsZero()) system.RemoveAt(i);
            }
        }

        public override string ToString(){
            string ret = "";
            foreach (Equation e in system){
                ret += e.ToString() + "\n";
            }
            return ret;
        }
    }

    static class IListExtensions{
        public static void Swap<T>(this IList<T> list, int i1, int i2){
            if (i1 == i2) return;
            T tmp = list[i1];
            list[i1] = list[i2]; list[i2] = tmp;
        }
    }
}