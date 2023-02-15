// Tyler Fichiera
// Quiz 2 - 02.06.23

// 1.a
var age: Int?

// 1.b
let gravity: Double = 9.8

// 2
let rfm: Double = 21
switch rfm {
case 0...20:
    print("You are Underfat")
case 20...35:
    print("You are Healthy")
case 35...42:
    print("You are Overfat")
case 42...:
    print("You are Obese")
default:
    print("input rfm cannot be less than 0")
}

// 3.a
let ex: String = "Hello"
var exRev: String = ""
for i in stride(from: ex.count - 1, through: 0, by: -1) {
    var ch = ex[ex.index(ex.startIndex, offsetBy: i)]
    exRev += String(ch)
}
print(exRev)

// 3.b
let ex2: String = "Hello my name is Tyler"
var ex2Rev: String = ""
for word in ex2.split(separator: " ") {
    var wordRev: String = ""
    for i in stride(from: word.count - 1, through: 0, by: -1) {
        var ch = word[word.index(word.startIndex, offsetBy: i)]
        wordRev += String(ch)
    }
    ex2Rev += wordRev + " "
}
print(ex2Rev)

// 4.i
func sumsOfArr(arr: [Int]) -> (sumOdd: Int, sumEven: Int) {
    var sumOdd: Int = 0
    var sumEven: Int = 0
    
    for n in arr {
        if n > 0 {
            if n % 2 == 0 {
                sumEven += n
            } else {
                sumOdd += n
            }
        }
    }
    
    return (sumOdd, sumEven)
}
let nums: [Int] = [1, 5, 6, 7, 8, 2, 10, 9, 11, 13, -1, -10, 0]
let res = sumsOfArr(arr: nums)
print(res)

// 4.ii
func getShortAndLong(arr: [String]) -> (shortestLen: Int, longestLen: Int) {
    if arr.count == 0 {
        return (0, 0)
    }
    
    var shortestLen = arr.first!.count
    var longestLen = arr.first!.count
    
    for str in arr {
        let c = str.count
        
        if c > longestLen {
            longestLen = c
        }
        
        if c < shortestLen {
            shortestLen = c
        }
    }
    
    return (shortestLen, longestLen)
}
let strs: [String] = ["Hello", "my", "name", "is", "Tyler!!"]
let res2 = getShortAndLong(arr: strs)
print(res2)

// 4.iii
func squentialSearch(nums: [Int], item: Int) -> Bool {
    for n in nums {
        if n == item {
            return true
        }
    }
    return false
}
let nums2 = [1, 2, 3, 4, 5, 6, 7, 8]
let res3 = squentialSearch(nums: nums2, item: 11)
print(res3)

// 5
class CityStatistics {
    var cityName: String
    var population: Int
    var latitude: Double
    var longitude: Double
    
    init(cityName: String, population: Int, longitude: Double, latitude: Double) {
        self.cityName = cityName
        self.population = population
        self.longitude = longitude
        self.latitude = latitude
    }
    
    func getPopulation() -> Int {
        return population
    }
    
    func getLatitude() -> Double {
        return latitude
    }
}

// 6.a
var cityStatisticsDict = [String: CityStatistics]()

cityStatisticsDict["Phoenix"] = CityStatistics(
    cityName: "Phoenix",
    population: 1625000,
    longitude: 112.0740,
    latitude: 33.4484
)
cityStatisticsDict["Paris"] = CityStatistics(
    cityName: "Paris",
    population: 2148000,
    longitude: 2.35221,
    latitude: 48.85662
)
cityStatisticsDict["London"] = CityStatistics(
    cityName: "London",
    population: 8787000,
    longitude: -0.1271,
    latitude: 51.5072
)
cityStatisticsDict["Madrid"] = CityStatistics(
    cityName: "Madrid",
    population: 3165000, //3165000
    longitude: -3.7040,
    latitude: 40.4169
)
cityStatisticsDict["Rome"] = CityStatistics(
    cityName: "Rome",
    population: 2867000,
    longitude: 12.4900,
    latitude: 41.8900
)

// 6.b
var largest: CityStatistics = cityStatisticsDict.first!.value
for city in cityStatisticsDict {
    if city.value.population > largest.population {
        largest = city.value
    }
}
print("Largest City Name: \(largest.cityName)")
print("Largest City Population: \(largest.population)")

// 6.c
var highest: CityStatistics = cityStatisticsDict.first!.value
for city in cityStatisticsDict {
    if city.value.latitude > highest.latitude {
        highest = city.value
    }
}
print("Northern Most City Name: \(highest.cityName)")
print("Northern Most City Latitude: \(highest.latitude)")

// 7
var students = [
    [ "firstName": "John", "lastName": "Wilson", "gpa": 2.4 ],
    [ "firstName": "Nancy", "lastName": "Smith", "gpa": 3.5 ],
    [ "firstName": "Michael", "lastName": "Liu", "gpa": 3.1 ]
]
var smartest = students[0]
for student in students {
    let gpa1 = student["gpa"] as! Double
    let gpa2 = smartest["gpa"] as! Double
    if gpa1 > gpa2 {
        smartest = student
    }
}
print("Highest GPA: \(smartest["firstName"] as! String) \(smartest["lastName"] as! String)")
