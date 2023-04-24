//
//  ContentView.swift
//  Lab8_EC
//
//  Created by Tyler Fichiera on 4/23/23.
//

import SwiftUI

struct Apple: Identifiable {
    var id = UUID()
    var position: CGPoint
}

struct ContentView: View {
    @State var monkeyPosition: CGPoint = CGPoint(x: 150, y: 150)
    @State var apples: [Apple] = []
    @State var timeRemaining = 10
    @State var showAlert = false
    
    var body: some View {
        VStack {
            ZStack {
                ForEach(apples, id: \.id) { apple in
                    Text("🍎")
                        .font(.system(size: 40))
                        .position(apple.position)
                }
                Text("🐒")
                    .font(.system(size: 80))
                    .position(monkeyPosition)
            }
            VStack {
                HStack {
                    Button("⬆️") {
                        if monkeyPosition.y > 0 {
                            monkeyPosition.y -= 50
                            checkCollision()
                        }
                    }
                }
                HStack {
                    Button("⬅️") {
                        if monkeyPosition.x > 0 {
                            monkeyPosition.x -= 50
                            checkCollision()
                        }
                    }
                    .padding(.horizontal, 10)
                    Button("➡️") {
                        if monkeyPosition.x < 400 {
                            monkeyPosition.x += 50
                            checkCollision()
                        }
                    }
                    .padding(.horizontal, 10)
                }
                .padding(.vertical, 5)
                HStack {
                    Button("⬇️") {
                        if monkeyPosition.y < 400 {
                            monkeyPosition.y += 50
                            checkCollision()
                        }
                    }
                }
                Text("Timer: \(timeRemaining)").padding(.vertical, 20)
            }
        }
        .onAppear {
            // load apples
            for _ in 0..<4 {
                let randomX = Int.random(in: 0..<400)
                let randomY = Int.random(in: 0..<400)
                let apple = Apple(position: CGPoint(x: randomX, y: randomY))
                apples.append(apple)
            }
            
            Timer.scheduledTimer(withTimeInterval: 1, repeats: true) { timer in
                if self.timeRemaining > 0 {
                    self.timeRemaining -= 1
                } else {
                    showAlert = true
                    timer.invalidate()
                }
            }
        }
        .alert(isPresented: $showAlert, content: {
            Alert(
                title: Text(apples.count > 0 ? "Time's up!" : "Winner!"),
                dismissButton: .default(Text("OK"))
            )
        })
    }
    
    func checkCollision() {
        for i in 0..<apples.count {
            if distance(monkeyPosition, apples[i].position) < 40 {
                apples.remove(at: i)
                break
            }
        }
        
        if apples.count == 0 {
            showAlert = true
            timeRemaining = 0
        }
    }
    
    func distance(_ p1: CGPoint, _ p2: CGPoint) -> CGFloat {
        let xDist = p2.x - p1.x
        let yDist = p2.y - p1.y
        return CGFloat(sqrt(xDist * xDist + yDist * yDist))
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
