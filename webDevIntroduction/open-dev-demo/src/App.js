import './App.css';

function Recipe() {
  const recipes = [<div className="content">
  <h3> function <b> cook_beef_burger </b> (ingredients: Food[]): Burger </h3>
    <ul>
      <li> <b>mix</b> (ground_beef, minced_onion, garlic_powder, salt, black_pepper) </li>
      <li> <b>shape_into_patties</b> () </li>
      <li> <b>grill_or_pan_fry_patties</b>() </li>
      <li> <b>toast_burger_buns</b>() </li>
      <li> <b>assemble_burger</b>() </li>
    </ul>
</div>,
<div className="content">
      <h3> function <b> cook_veggie_quinoa_burger</b> (ingredients: Food[]): Burger </h3>
      <ul>
        <li> <b>mix</b> (quinoa, mashed_black_beans, diced_bell_peppers, chopped_onions, breadcrumbs, spices) </li>
        <li> <b>shape_into_patties</b> () </li>
        <li> <b>pan_fry_or_bake_patties</b>() </li>
        <li> <b>toast_burger_buns</b>() </li>
        <li> <b>assemble_burger</b>() </li>
      </ul>
    </div>,
    <div className="content">
    <h3> function <b> cook_grilled_chicken_teriyaki_burger </b> (ingredients: Food[]): Burger </h3>
    <ul>
      <li> <b>marinate_chicken</b>()</li>
      <li> <b>grill</b> (chicken)</li>
      <li> <b>toast</b> (burger_buns) </li>
      <li> <b>prepare_spicy_mayo</b>() </li>
      <li> <b>assemble_burger</b>() </li>
    </ul>
  </div>];
  return recipes[value];
}

function App() {
  return <h1>TEST HERE</h1>;
}

export default App;


// import logo from './logo.svg';

// import './App.css';

// function App() {
//   return (
//     <div className="App">
//       <header className="App-header">
//         <img src={logo} className="App-logo" alt="logo" />
//         <p>
//           Edit <code>src/App.js</code> and save to reload.
//         </p>
//         <a
//           className="App-link"
//           href="https://reactjs.org"
//           target="_blank"
//           rel="noopener noreferrer"
//         >
//           Learn React
//         </a>
//       </header>
//     </div>
//   );
// }

// export default App;
