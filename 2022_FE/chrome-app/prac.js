function handleMouseLeave()
{
    h1.innerText = "mouse is gone!";
}

function handleWindowResize()
{
    document.body.style.backgroundColor = "tomato";
}

function handleWindowCopy()
{
    alert("copier!");
}

function handleWindowOffline()
{
    alert("SOS no WIFI");
}

function handleWindowOnline()
{
    alert("ALL Goood");
}

h1.addEventListener("click", handTitleClick);
h1.addEventListener("mouseenter", handleMouseEnter);
h1.addEventListener("mouseleave", handleMouseLeave);

window.addEventListener("resize", handleWindowResize);
window.addEventListener("copy", handleWindowCopy);
window.addEventListener("offline", handleWindowOffline);
window.addEventListener("offline", handleWindowOnline);


//2
const h1 = document.querySelector("div.hello:first-child h1");

function handTitleClick()
{
    const currentColor = h1.style.color;
    let newColor;
    if(currentColor === "blue")
    {
        newColor = "tomato";
    }
    else
    {
        newColor = "blue";
    }
    h1.style.color = newColor;
}

h1.addEventListener("click", handTitleClick);

//3
const h1 = document.querySelector("div.hello:first-child h1");

function handTitleClick()
{
    const clickedClass = "clicked";
    if(h1.classList.contains(clickedClass))
    {
        h1.classList.remove(clickedClass);
    }
    else
    {
        h1.classList.add(clickedClass);
    }

    //위에 거랑 같음
    // h1.classList.toggle("clicked");

}

h1.addEventListener("click", handTitleClick);

//login
// const loginForm = document.getElementById("login-form");
// const loginInput = loginForm.querySelector("input");
// const loginButton = loginForm.querySelector("button");
const loginInput = document.querySelector("#login-form input");
const loginButton = document.querySelector("#login-form button");

function onLoginBtnClick()
{
    console.log(loginInput.value);
}


loginButton.addEventListener("click", onLoginBtnClick);
