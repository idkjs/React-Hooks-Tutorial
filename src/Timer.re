module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

type state = {
  seconds: int,
  isTicking: bool,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Start => {...state, isTicking: true}
        | Stop => {...state, isTicking: false}
        | Reset => {...state, seconds: 30}
        | Tick => state.isTicking && state.seconds > 0 ? {...state, seconds: state.seconds - 1}: state
        },
      // The second argument to useReducer is the initial state of the reducer.
      {isTicking: true, seconds: 3},
    );
  // To update the timer every second, we need to create an effect.
  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div>
    {ReasonReact.string(
       "There are " ++ string_of_int(state.seconds) ++ " on the clock",
     )}
     {state.isTicking
        ? <Button label="STOP" onClick={_event => dispatch(Stop)} />
        : <>
            <Button label="START" onClick={_event => dispatch(Start)} />
            <Button label="RESET" onClick={_event => dispatch(Reset)} />
          </>}
  </div>;
};