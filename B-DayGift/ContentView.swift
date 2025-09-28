import SwiftUI
import Foundation
import WebKit

struct Question {
    let text: String
    let answers: [String]
    let correctAnswer: String?
    let isOpinion: Bool
    let explanation: String
}

struct BirthdayBackground<Content: View>: View {
    let content: Content
    
    init(@ViewBuilder content: () -> Content) {
        self.content = content()
    }

    var body: some View {
        ZStack {
            Image("birthdayBackground")
                .resizable()
                .scaledToFill()
                .ignoresSafeArea()
            content
        }
    }
 }

struct TextBox: View {
    var text: String
    var body: some View {
        Text(text)
            .padding()
            .frame(maxWidth: .infinity)
            .background(
                RoundedRectangle(cornerRadius: 12)
                    .fill(Color.white.opacity(0.8))
                    .shadow(radius: 5)
            )
            .foregroundColor(.black)
            .padding(.horizontal)
    }
}

struct FramedBox<Content: View>: View {
    let content: Content
    
    init(@ViewBuilder content: () -> Content) {
        self.content = content()
    }
    
    var body: some View {
        content
            .padding()
            .background(
                RoundedRectangle(cornerRadius: 24)
                    .strokeBorder(
                        LinearGradient(
                            colors: [.pink, .purple, .blue],
                            startPoint: .topLeading,
                            endPoint: .bottomTrailing
                        ),
                        lineWidth: 6
                    )
                    .shadow(radius: 10)
            )
            .padding()
    }
}

struct BorderedContainer<Content: View>: View {
    let content: Content
    
    init(@ViewBuilder content: () -> Content) {
        self.content = content()
    }
    
    var body: some View {
        GeometryReader { geo in
            ZStack {
                Image("birthdayBackground")
                    .resizable()
                    .scaledToFill()
                    .frame(width: geo.size.width, height: geo.size.height)
                    .clipped()

                VStack {
                    content
                }
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .padding()
                .background(
                    RoundedRectangle(cornerRadius: 24)
                        .fill(Color.white.opacity(0.7))
                        .overlay(
                            RoundedRectangle(cornerRadius: 24)
                                .stroke(
                                    LinearGradient(
                                        colors: [.pink, .purple, .blue],
                                        startPoint: .topLeading,
                                        endPoint: .bottomTrailing
                                    ),
                                    lineWidth: 8
                                )
                        )
                )
                .padding(20)
            }
            .frame(width: geo.size.width, height: geo.size.height)
        }
        .ignoresSafeArea()
    }
}

struct Balloon: View {
    var color: Color
    var body: some View {
        VStack(spacing: 0) {
            Ellipse()
                .fill(color)
                .frame(width: 40, height: 55)
                .overlay(
                    Ellipse()
                        .stroke(Color.white.opacity(0.6), lineWidth: 2)
                        .offset(x: -5, y: -5)
                )
            
            Rectangle()
                .fill(Color.gray)
                .frame(width: 2, height: 30)
        }
    }
}

struct FloatingBalloon: View {
    var color: Color
    var delay: Double
    
    @State private var floatUp = false
    
    var body: some View {
        GeometryReader { geo in
            let screenWidth = geo.size.width
            let startX = CGFloat.random(in: 0...screenWidth)   // anywhere across
            let driftX = CGFloat.random(in: -150...150)
            let startY = geo.size.height + 100                 // start below screen
            
            Balloon(color: color)
                .offset(
                    x: floatUp ? startX + driftX : startX,
                    y: floatUp ? -200 : startY
                )
                .opacity(floatUp ? 0 : 1)
                .animation(
                    .easeInOut(duration: Double.random(in: 6...10)).delay(delay),
                    value: floatUp
                )
                .onAppear { floatUp = true }
        }
    }
}

struct ConfettiPiece: View {
    var color: Color
    var size: CGFloat
    
    var body: some View {
        Rectangle()
            .fill(color)
            .frame(width: size, height: size * 0.4) // little strips
            .rotationEffect(.degrees(Double.random(in: 0...360)))
    }
}

struct FallingConfetti: View {
    var color: Color
    var delay: Double
    
    @State private var fall = false
    
    var body: some View {
        GeometryReader { geo in
            let screenWidth = geo.size.width
            let startX = CGFloat.random(in: 0...screenWidth)   // anywhere across the screen
            let driftX = CGFloat.random(in: -150...150)
            let size = CGFloat.random(in: 6...12)
            
            ConfettiPiece(color: color, size: size)
                .offset(
                    x: fall ? startX + driftX : startX,
                    y: fall ? geo.size.height + 100 : -100
                )
                .rotationEffect(.degrees(fall ? 720 : 0))
                .opacity(fall ? 0 : 1)
                .animation(
                    .easeInOut(duration: Double.random(in: 4...7)).delay(delay),
                    value: fall
                )
                .onAppear {
                    fall = true
                }
        }
    }
}

struct AnimatedQuestionView: View {
    let question: Question
    @Binding var selectedAnswer: String?
    let answerAction: (String) -> Void
    
    @State private var animateQuestion = false
    @State private var animateButtons = false
    
    var body: some View {
        VStack(alignment: .leading, spacing: 20) {
            TextBox(text: question.text)
                .font(.headline)
                .multilineTextAlignment(.leading)
                .opacity(animateQuestion ? 1 : 0)
                .offset(y: animateQuestion ? 0 : 20)
                .animation(.easeOut(duration: 0.6), value: animateQuestion)
            
            ForEach(question.answers.indices, id: \.self) { index in
                Button(action: {
                    selectedAnswer = question.answers[index]
                    answerAction(question.answers[index])
                }) {
                    Text(question.answers[index])
                        .padding()
                        .frame(maxWidth: .infinity, alignment: .leading)
                        .background(Color.red.opacity(0.3))
                        .cornerRadius(8)
                }
                .opacity(animateButtons ? 1 : 0)
                .offset(y: animateButtons ? 0 : 20)
                .animation(
                    .easeOut(duration: 0.5)
                        .delay(Double(index) * 0.2),
                    value: animateButtons
                )
            }
            
            Spacer()
        }
        .padding()
        .onAppear {
            animateQuestion = true
            animateButtons = true
        }
    }
}

struct FeedbackCardView: View {
    let title: String
    let message: String?
    let buttonTitle: String
    let buttonAction: () -> Void

    @State private var show = false

    var body: some View {
        FramedBox {
            VStack {
                Spacer()
                
                TextBox(text: title)
                    .font(.largeTitle)
                    .multilineTextAlignment(.center)
                    .scaleEffect(show ? 1 : 0.5)
                    .opacity(show ? 1 : 0)
                    .animation(.spring(response: 0.5, dampingFraction: 0.55), value: show)

                if let message {
                    TextBox(text: message)
                        .multilineTextAlignment(.center)
                        .opacity(show ? 1 : 0)
                        .offset(y: show ? 0 : 24)
                        .animation(.easeOut(duration: 0.6).delay(0.15), value: show)
                }

                Spacer()
                HStack {
                    Spacer()
                    Button(action: { buttonAction() }) {
                        Text(buttonTitle)
                            .font(.headline)
                            .padding(.horizontal, 24)
                            .padding(.vertical, 12)
                            .background(Color.pink)
                            .foregroundColor(.white)
                            .cornerRadius(10)
                    }
                    .contentShape(Rectangle())
                }
                .padding()
            }
        }
        .onAppear {
            show = false
            DispatchQueue.main.async { show = true }
        }
    }
}

struct FestiveQuestionView: View {
    let question: Question
    @Binding var selectedAnswer: String?
    let answerAction: (String) -> Void
    
    @State private var animateQuestion = false
    @State private var animateButtons = false
    
    let festiveGradients: [LinearGradient] = [
        LinearGradient(colors: [.pink, .purple], startPoint: .topLeading, endPoint: .bottomTrailing),
        LinearGradient(colors: [.orange, .yellow], startPoint: .top, endPoint: .bottom),
        LinearGradient(colors: [.blue, .cyan], startPoint: .leading, endPoint: .trailing),
        LinearGradient(colors: [.green, .mint], startPoint: .topTrailing, endPoint: .bottomLeading)
    ]
    
    var body: some View {
        VStack(alignment: .leading, spacing: 20) {
            Text("\(question.text)")
                .font(.title3.bold())
                .multilineTextAlignment(.center)
                .padding()
                .background(
                    RoundedRectangle(cornerRadius: 20)
                        .fill(LinearGradient(colors: [.pink.opacity(0.8), .purple.opacity(0.8)], startPoint: .topLeading, endPoint: .bottomTrailing))
                        .shadow(color: .pink.opacity(0.6), radius: 10, x: 0, y: 5)
                )
                .opacity(animateQuestion ? 1 : 0)
                .scaleEffect(animateQuestion ? 1 : 0.8)
                .animation(.spring(response: 0.6, dampingFraction: 0.7), value: animateQuestion)
            
            ForEach(question.answers.indices, id: \.self) { index in
                Button(action: {
                    selectedAnswer = question.answers[index]
                    answerAction(question.answers[index])
                }) {
                    Text(question.answers[index])
                        .font(.headline)
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(
                            festiveGradients[index % festiveGradients.count]
                                .cornerRadius(16)
                        )
                        .foregroundColor(.white)
                        .shadow(color: .black.opacity(0.25), radius: 6, x: 0, y: 3)
                        .scaleEffect(selectedAnswer == question.answers[index] ? 1.1 : 1.0)
                        .animation(.spring(response: 0.4, dampingFraction: 0.6), value: selectedAnswer)
                }
                .opacity(animateButtons ? 1 : 0)
                .offset(y: animateButtons ? 0 : 20)
                .animation(.easeOut(duration: 0.5).delay(Double(index) * 0.2), value: animateButtons)
            }
            
            Spacer()
        }
        .padding()
        .onAppear {
            animateQuestion = true
            animateButtons = true
        }
    }
}

struct ContentView: View {
    @State private var screen: Screen = .launch
    @State private var questionIndex = 0
    @State private var selectedAnswer: String? = nil
    @State private var showGiftImage = false
    @State private var launchAnimate = false
    @State private var explainAnimate = false
    @State private var scaleAnimate = false
    
    let questions: [Question] = [
        Question(
            text: "¿Cual es mi parte favorita de ti?",
            answers: ["Tu sonrisa", "Tu risa", "Todo de ti me encanta", "Tu amabilidad"],
            correctAnswer: "Todo de ti me encanta",
            isOpinion: false,
            explanation: "¡Correcto! Desde tu carita, hasta tus pies, me encanta todo de ti. ¡Te amo!💘",
        ),
        Question(
            text: "¿Cual fue la ultima vez que me enamore de ti?",
            answers: ["El dia en que nos conocimos", "Me sigo enamorando de ti cada dia", "El dia de nuestro primer beso", "En nuestra primera cita"],
            correctAnswer: "Me sigo enamorando de ti cada dia",
            isOpinion: false,
            explanation: "No hay dia que no me enamore de ti...😘",
        ),
        Question(
            text: "Si pudieras tener un regalo magico el dia de tu cumpleaños, ¿cual seria?",
            answers: ["Un gato que habla", "Unas vacaciones a todos los lugares", "Pastel infinito", "Un dia donde el tiempo se detiene"],
            correctAnswer: nil,
            isOpinion: true,
            explanation: "¡Que interesante! Eso me habla mucho de ti :3",
        ),
        Question(
            text: "¿Que postre describe tu personalidad mejor?",
            answers: ["Pastel de lava de chocolate: Calida y con gran personalidad", "Dulce de algodon: Dulce y divertida", "Pastel de queso: Creativa y con mente abierta", "Macaronni: Colorida y elegante"],
            correctAnswer: nil,
            isOpinion: true,
            explanation: "Yo opino que todos te quedan a ti corazon😍",
        ),
        Question(
            text: "Si yo planeara tu fiesta de cumpleaños, ¿que es lo que DEFINITIVAMENTE haria?",
            answers: ["Globos con tu cara en ellos", "Un numbero de baile sorpresa", "Un pastel gigante", "Todo lo anterior"],
            correctAnswer: "Todo lo anterior",
            isOpinion: false,
            explanation: "Me gustaria sacarte una sonrisa :)",
        ),
        Question(
            text: "¿Cual seria la forma mas exagerada de decirte feliz cumpleaños?",
            answers: ["Multitud relampago", "Escritura en el cielo", "Telegram cantando", "Nombrar una estrella en tu honor"],
            correctAnswer: nil,
            isOpinion: true,
            explanation: "Cheetoss, en serio?? :O",
        )
    ]
    
    var body: some View {
        VStack {
            switch screen {
                
            case .launch:
                BorderedContainer {
                    FramedBox {
                        VStack {
                            Spacer()
                            TextBox(text: "Presiona Iniciar")
                                .font(.title)
                                .multilineTextAlignment(.center)
                                .scaleEffect(launchAnimate ? 1.05 : 0.95)
                                .opacity(launchAnimate ? 1 : 0)
                                .animation(
                                    .easeInOut(duration: 1).repeatForever(autoreverses: true),
                                    value: launchAnimate
                                )
                                .onAppear { launchAnimate = true }
                            Button(action: { screen = .explanation }) {
                                Text("Iniciar")
                                    .font(.headline)
                                    .padding(.horizontal, 24)
                                    .padding(.vertical, 12)
                                    .background(Color.pink)
                                    .foregroundColor(.white)
                                    .cornerRadius(10)
                            }
                            .contentShape(Rectangle())
                            Spacer()
                        }
                    }
                }
                    
                case .explanation:
                    BorderedContainer {
                        FramedBox{
                            VStack {
                                Spacer()
                                TextBox(text: "¡Bienvenida! En este juego deberas responder algunas preguntas para poder desbloquear tu regalo! Buena Suerte!!").multilineTextAlignment(.center)
                                    .offset(y: explainAnimate ? 0 : 100)
                                    .opacity(explainAnimate ? 1 : 0)
                                    .animation(.easeOut(duration: 1), value: explainAnimate)
                                    .onAppear { explainAnimate = true }
                                Spacer()
                                HStack {
                                    Spacer()
                                    Button(action: { screen = .question }) {
                                        Text("Siguiente")
                                            .font(.headline)
                                            .padding(.horizontal, 24)
                                            .padding(.vertical, 12)
                                            .background(Color.pink)
                                            .foregroundColor(.white)
                                            .cornerRadius(10)
                                    }
                                    .contentShape(Rectangle())
                                }
                                .padding()
                            }
                        }
                    }
                    
                case .question:
                    let q = questions[questionIndex]
                    BorderedContainer {
                        FramedBox{
                            FestiveQuestionView(
                                question: q,
                                selectedAnswer: $selectedAnswer,
                                answerAction: { answer in
                                    screen = evaluateAnswer(answer: answer, question: q)
                                }
                            )
                        }
                    }
                    
                case .correct(let explanation):
                    BorderedContainer {
                        FeedbackCardView(
                            title: "¡Correcto!",
                            message: explanation,
                            buttonTitle: "Siguiente",
                            buttonAction: { nextQuestion() }
                        )
                    }
                    
                case .incorrect:
                    BorderedContainer {
                        FeedbackCardView(
                            title: "Incorrecto, intenta de nuevo! :)",
                            message: nil,
                            buttonTitle: "Intentar de Nuevo",
                            buttonAction: { screen = .question }
                        )
                    }
                    
                case .opinion(let explanation):
                    BorderedContainer {
                        FeedbackCardView(
                            title: "Interesante",
                            message: explanation,
                            buttonTitle: "Siguiente",
                            buttonAction: { nextQuestion() }
                        )
                    }
                    
                case .gift:
                BorderedContainer {
                    FramedBox{
                            ZStack {
                                ForEach(0..<20) { _ in
                                    FloatingBalloon(
                                        color: [.pink, .blue, .purple, .red, .orange, .yellow].randomElement()!,
                                        delay: Double.random(in: 0...3)
                                    )
                                }
                                
                                ForEach(0..<40) { i in
                                    FallingConfetti(
                                        color: [.red, .blue, .yellow, .green, .purple, .pink, .orange].randomElement()!,
                                        delay: Double.random(in: 0...5)
                                    )
                                }
                                
                                HStack {
                                    VStack(alignment: .leading) {
                                        TextBox(text: "Lo Lograste!")
                                            .font(.title)
                                            .opacity(showGiftImage ? 1 : 0)
                                            .offset(y: showGiftImage ? 0 : 50)
                                            .animation(.easeOut(duration: 1.0), value: showGiftImage)
                                        TextBox(text: "Feliz Cumpleaños, Andrea!")
                                            .font(.title2)
                                    }
                                    Spacer()
                                    Image("herPhoto")
                                        .resizable()
                                        .aspectRatio(contentMode: .fit)
                                        .cornerRadius(10)
                                        .opacity(showGiftImage ? 1 : 0)
                                        .scaleEffect(showGiftImage ? 1 : 0.8)
                                        .animation(.easeOut(duration: 1.2), value: showGiftImage)
                                }
                                .padding()
                            }
                        }
                    }
                    .onAppear {
                        showGiftImage = true
                    }
            }
        }
    }
    
    func evaluateAnswer(answer: String, question: Question) -> Screen {
        if question.isOpinion {
            return .opinion(explanation: question.explanation)
        }
        guard let correct = question.correctAnswer else { return .incorrect}
        return answer == correct ? .correct(explanation: question.explanation) : .incorrect
    }
    
    func nextQuestion() {
        selectedAnswer = nil
        questionIndex += 1
        if questionIndex < questions.count {
            screen = .question
        } else {
            screen = .gift
        }
    }
    
    enum Screen {
        case launch
        case explanation
        case question
        case correct(explanation: String)
        case incorrect
        case opinion(explanation: String)
        case gift
    }
}
