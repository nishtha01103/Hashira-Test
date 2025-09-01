let input = "";
process.stdin.on("data", (chunk) => (input += chunk));
process.stdin.on("end", () => {
  // Parse JSON
  const data = JSON.parse(input);
  const n = data.keys.n;
  const k = data.keys.k;

  // Helper to convert string in given base to decimal (BigInt)
  function baseToDecimal(value, base) {
    return BigInt(parseInt(value, base));
  }
  let roots = [];
  for (let i = 1; i <= k; ++i) {
    const root = data[i.toString()];
    if (!root) continue;
    roots.push(baseToDecimal(root.value, parseInt(root.base)));
  }

  if (roots.length < k) {
    console.log("Not enough roots found in input.");
  } else {
    // For degree m = k-1: constant term is (-1)^k * r1*r2*...*rk
    let c = BigInt(1);
    for (let i = 0; i < k; ++i) c *= roots[i];
    if (k % 2 === 1) c = -c;
    console.log("The value of c is: " + c.toString());
  }
});
