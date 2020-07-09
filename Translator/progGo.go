package main
import(
	
	"fmt"	
	"math"
)

func main(){ 

var a,b,c int

fmt.Println("a = ")
fmt.Scan(a)

fmt.Println("b = ")
fmt.Scan(b)

fmt.Println("c = ")
fmt.Scan(c)

SqrEq(a,b,c)
}

func SqrEq(a,b,c int) {

	fmt.Println(a, "x^2", " + ", b, "x", " + ", c, " = 0; \n")


	var d int = b*b - 4*a*c

	if d < 0 {
		fmt.Println("The discriminant < 0 !\n")

	} else if d == 0 {
		math.Sqrt(d)
		var x int = -b / (2*a)
		fmt.Println("x = ")
		fmt.Println(x)
	} else {
		math.Sqrt(d)
		var x1 int= (-b + d) / (2*a)
		var x2 int= (-b - d) / (2*a)
		
		fmt.Println("x1 = ")
		fmt.Println(x1)

		fmt.Println("\n")

		fmt.Println("x2 = ")
		fmt.Println(x2)
	}
}