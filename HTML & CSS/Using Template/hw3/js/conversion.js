var report = function (platinum, usdollars) {
    if (!isNaN(parseFloat(platinum))) {
    document.getElementById("result").innerHTML =
        parseFloat(platinum).toFixed(0) + " Platinum = " + parseFloat(usdollars).toFixed(2) + " USD";
}
else {
    document.getElementById("result").innerHTML = "This converter only works with numbers.";
}
};

document.getElementById("usd_to_p").onclick = function () {
    var usd = document.getElementById("currency").value;
    report(usd_convert(usd), usd);
};

document.getElementById("p_to_usd").onclick = function () {
    var p = document.getElementById("currency").value;
    report(p, p_convert(p));
};

function usd_convert (dollars) {
    return (dollars * 15); //Converts US Dollars to platinum
}

function p_convert (platinum) {
    return (platinum / 15); // Converts platinum to US Dollars
}