/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:

    /*
     * Create a GameState with randomly placed, but not
     * overlapping hero and numberOfRobots robots
     */
    GameState(int numberOfRobots);

    /*
     * Destructor that deletes the units
     */
    ~GameState();

    /*
     * Copys the constructor
     */
    GameState(const GameState& prev);

    /*
     * Assign the copied constructor
     */
    GameState& operator= (const GameState& prev);

    /*
     * Makes the deep copy
     */
    void deepCopy (const GameState& prev);

    /*
     * Clear and redraw entire playing field
     */
    void draw(QGraphicsScene* scene) const;	// Clear and redraw entire playing field

    /*
     * Teleport hero to random location
     */
    void teleportHero();

    /*
     * Move robots one step towards hero
     */
    void moveRobots();

    /*
     * Identify crashed robots
     */
    void updateCrashes();

    /*
     * Count identified crashed robots
     */
    int countToBeJunked()const;

    /*
     * Replace each identified crashed robot with a junk
     */
    void junkTheCrashed();

    /*
     * Are there still robots that did not crash?
     */
    bool someRobotsAlive() const;

    /*
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /*
     * Move hero towards dir
     */
    void moveHeroTowards (const Point& dir);

    /*
     * Return hero
     */
    Point getHeroAsPoint () const;

private:
    std::vector<Unit*> units;    // the robots and junks
    Hero hero;                  // the hero

    // private helpers
    bool isEmpty(const Unit& unit) const;

};

#endif // GAMESTATE_H
