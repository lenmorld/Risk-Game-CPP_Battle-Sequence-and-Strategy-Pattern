Risk Battle Strategy Pattern

Integrated as a part of Risk Game project

Strategy Pattern
*	Context Class – Player
    *	Player uses a certain behavior that can be changed during execution
    *	Contains a Strategy object, provides a setStrategy() method to change its own strategy
    *	The strategy is called through a executeStrategy() method that will delegate to a concrete strategy method
    *	Strategy Abstract Class – Strategy
    *	Superclass of all Strategies containing the abstract executeStrategy() to be implemented by all its subclasses
    
*	Concrete Strategies – subclasses of Strategy the provide a different implementation for the executeStrategy() method
    *	Aggressive – always attack if the player controls a country that has one adjacent enemy country with less armies than it has
        *	for this assignment, after calculating whether to attack or not, if attacking, then the valid country to use and valid country to attack are automatically chosen based on the best advantage
    *	Defensive – never attack unless the player controls a country for which all adjacent enemy countries have significantly less armies
        *	for this assignment, after calculating whether to attack or not, if attacking, then the valid country to use and valid country to attack are automatically chosen based on the best advantage
    *	Random – randomly choose between attacking or not, then if attacking, choose a random valid target
    *	Normal – manual / user must decide whether to attack or not, which country to use and which one to attack 

Battle Phase Rules used

Rules followed are from the Assignment 1 handout, with the addition of consulting  http://www.hasbro.com/common/instruct/risk.pdf.

1.  The player chooses one of the countries he owns with >= 2 armies,
2.  Declares an attack on an adjacent country that is owned by another player.
3. A battle is then simulated by the attacker choosing to roll at most 3 dice, and the defender choosing to roll at most 2 dice .
A document from Hasbro Risk is consulted, http://www.hasbro.com/common/instruct/risk.pdf
regarding the choice of number of dices for attacker and defender.
It says in the document, page 9
"You, the attacker, will roll 1,2 or 3  dice: You must have at least one
more army in your territory than the number of dice you roll.
The defender will roll either 1 or 2  dice: To roll 2 dice, he or she
must have at least 2 armies on the territory under attack. "
4. Best dice rolls are compared between attacker and defender. If the next dice roll of attacker <= defender,
attacker loses one army(dice). If attacker > defender, defender loses one army(dice).
5. If the defender rolled two dice then the 2nd best dice are compared, as in (4)
6. The attacker can choose to continue attacking until either all his armies or all the defending armies
have been eliminated.
7. If all the defender's armies are eliminated the attacker captures the territory.
8. The attacking player must place a number of armies in the conquered country which >= dice used in attack that resulted in conquering the country.
9. There must be an “all-in” attack mode that uses the maximum number of dice on both sides and runs automatically until the attack results in either
a) The defending country to be conquered and all armies of the conquering country are moved to the conquered country
or b) the attacking country runs out of armies and cannot attack anymore.

Rules followed are from the Assignment 1 handout, with the addition of consulting  http://www.hasbro.com/common/instruct/risk.pdf.


