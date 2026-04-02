const calendar = document.getElementById("calendar");
const dayView = document.getElementById("dayView");

const baseSchedule = [
    { time: "6:30–7:30", task: "Morning Walk" },
    { time: "3:00–6:00", task: "Deep Work / Case Study / Subject" },
    { time: "6:00–7:00", task: "AI / ML Unit" },
    { time: "7:00–8:00", task: "Evening Walk" },
    { time: "8:00–9:00", task: "DSA (3 Questions)" },
    { time: "9:00–9:45", task: "Lab / SQL / Excel" },
    { time: "10:15+", task: "❤️ Phone Discipline" }
];

// Create April calendar
for (let i = 3; i <= 30; i++) {
    let div = document.createElement("div");
    div.className = "day-box";
    div.innerText = i;

    div.onclick = () => openDay(i);

    calendar.appendChild(div);
}

// Load saved data
let data = JSON.parse(localStorage.getItem("planner")) || {};

function getSymbol(status) {
    return ["❌", "◔", "◐", "✔"][status];
}

function getValue(status) {
    return [0, 0.25, 0.5, 1][status];
}

function openDay(day) {
    if (!data[day]) {
        data[day] = baseSchedule.map(t => ({
            ...t,
            status: 0
        }));
    }

    let html = `<h2>April ${day}</h2>`;
    let total = 0, done = 0;

    data[day].forEach((item, idx) => {
        total += 1;
        done += getValue(item.status);

        html += `
            <div class="task">
                ${item.time} → ${item.task}
                <button onclick="update(${day}, ${idx})">
                    ${getSymbol(item.status)}
                </button>
            </div>
        `;
    });

    let percent = (done / total) * 100;

    html += `<h3>Progress: ${percent.toFixed(0)}%</h3>`;

    dayView.innerHTML = html;

    localStorage.setItem("planner", JSON.stringify(data));
}

function update(day, index) {
    data[day][index].status = (data[day][index].status + 1) % 4;
    openDay(day);
}
