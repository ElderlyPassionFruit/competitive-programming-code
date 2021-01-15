private fun readLn() = readLine()!! // string line
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readInt() = readLn().toInt() // single int

fun main(args: Array<String>) {
    var t = readInt()
  	while (t-- > 0) {
    	var (n, k) = readInts()
    	var n1 = n / (1 + k + k * k + k * k * k)
  
		var a = ArrayList<Int>()
		a.add(n1)
		a.add(n1 * k)
		a.add(n1 * k * k)
		a.add(n1 * k * k * k)
		println(a.joinToString(" "))
    }
}