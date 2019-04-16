# pomodoro-timer

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

## Hooks
For our timer, we need to keep track of at least two things:

    The seconds on the clock
    Whether it is ticking or not

When we consider any timer, we usually have three buttons: Start, Stop, and Reset. These map to directly to user interactions, but there is one more: the Tick itself. Even though the tick is not controlled by the user, it is still an action that should return a new state for our reducer.

At the top of Timer.re, where we will build this whole app, add the following:

```reason
type state = {
  seconds: int,
  isTicking: bool
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;
```