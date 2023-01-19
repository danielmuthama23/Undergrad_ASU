//
//  ViewController.swift
//  1_Storyboard
//
//  Created by Tyler Fichiera on 1/18/23.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        self.greetingLabel.isHidden = true
        // Do any additional setup after loading the view.
    }

    @IBOutlet weak var firstNameField: UITextField!
    @IBOutlet weak var lastNameField: UITextField!
    @IBOutlet weak var greetingLabel: UILabel!
    
    @IBAction func onGreetingClick(_ sender: Any) {
        let firstName = self.firstNameField.text!
        let lastName = self.lastNameField.text!
        
        self.greetingLabel.text = "\(firstName) \(lastName) Welcome to CSE 335"
        self.greetingLabel.isHidden = false
    }
}

