% CSE240 Fall 2021 HW13
% Tyler Fichiera
% Question 2

% Q2.1 - Student's school, subject, and course facts

% school/2
school(alex, cidse).
school(jennifer, ssebe).
school(tyler, cidse).

subject(alex, computer_science).
subject(alex, software_eng).

subject(jennifer, construction_eng).
subject(jennifer, environmental_eng).

subject(tyler, computer_science).
subject(tyler, software_eng).

course(computer_science, 'CSE240').
course(computer_science, 'CSE310').
course(computer_science, 'CSE445').

course(software_eng, 'SER222').
course(software_eng, 'SER321').
course(software_eng, 'SER322').

course(construction_eng, 'CNE210').
course(construction_eng, 'CNE213').
course(construction_eng, 'CNE243').

course(environmental_eng, 'EVE214').
course(environmental_eng, 'EVE261').
course(environmental_eng, 'EVE305').

% Q2.2 - Info rule
% returns the school and subjects
info(X, Y) :- school(X, Y); subject(X, Y).

% Q2.3 - Schedule info
schedule(X, Y) :- subject(X, Z), course(Z, Y).

% Test cases:
q2_2 :- info(alex, X),
    write(X),
    nl.

q2_3 :- schedule(jennifer, X),
    write(X),
    nl.
