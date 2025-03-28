class Poly:
    def __init__(self, capacity=10):
        self.degree = 0
        self.coef = [0] * capacity if capacity else []

    def readPoly(self):
        self.degree = int(input("Input polynomial degree: "))
        for i in range(self.degree, -1, -1):
            c = int(input("%d차 항의 계수: " %i))
            self.coef[i] = c
        
    def printPoly(self):
        strr = ""
        for i in range(self.degree, 0, -1):
            coef = self.coef[i]
            if coef != 0:
                sign = " + " if coef > 0 and strr else (" - " if coef < 0 and strr else ("-" if coef < 0 else ""))
                abs_coef = abs(coef)
                if i == 1:
                    strr += f"{sign}{abs_coef}x"
                else:
                    strr += f"{sign}{abs_coef}x^{i}"

        if self.coef[0] != 0:
            sign = " + " if self.coef[0] > 0 and strr else (" - " if self.coef[0] < 0 and strr else ("-" if self.coef[0] < 0 else ""))
            strr += f"{sign}{abs(self.coef[0])}"

        print(strr)


    def add(self):
        second = Poly()
        second.readPoly()

        max_deg = self.degree if self.degree > second.degree else second.degree

        a_coef = self.coef + [0] * (max_deg - self.degree)
        b_coef = second.coef + [0] * (max_deg - second.degree)

        result_coef = [a_coef[i] + b_coef[i] for i in range(max_deg + 1)]

        print("Sum of Polynomials:")

        strr = ""
        for i in range(len(result_coef)-1, 0, -1):
            coef = result_coef[i]
            if coef != 0:
                sign = " + " if coef > 0 and strr else (" - " if coef < 0 and strr else ("-" if coef < 0 else ""))
                abs_coef = abs(coef)
                if i == 1:
                    strr += f"{sign}{abs_coef}x"
                else:
                    strr += f"{sign}{abs_coef}x^{i}"

        if result_coef[0] != 0:
            sign = " + " if result_coef[0] > 0 and strr else (" - " if result_coef[0] < 0 and strr else ("-" if result_coef[0] < 0 else ""))
            strr += f"{sign}{abs(result_coef[0])}"

        print(strr)

    def eval(self):
        b = 0
        value = int(input("Please enter x value:\n"))
        for i in range(self.degree,0,-1):
            b += (value**i)*self.coef[i]
        return b + self.coef[0]


if __name__ == "__main__":
    a = Poly()
    a.readPoly()
    a.printPoly()
    result = a.eval()
    print(f"Result of evaluation: {result}\n")

    print("Adding to 2 polynomials\n")

    a.add()
