const fs = require('fs')
const str = fs.readFileSync(__dirname + '/keymap.c', 'utf8')

const matches = str.match(/\[.+LAYOUT\( \\[\s\S]+?\)/g)

const mapsString = matches
  .map((m, i) => {
    const rows = m
      .split('\\')
      .slice(1, -1)
      .map((row, i) => {
        const filtered = row
          .split(',')
          .map(k => k.trim())
          .filter(k => k)

        if (i < 3) filtered.splice(6, 0, null, null)

        return filtered.map(k => {
          return k === null
            ? null
            : k === 'XXXXXXX'
            ? ''
            : k.startsWith('KC_') || k.startsWith('JP_')
            ? k.slice(3)
            : k
        })
      })
      .filter(row => row.length)
      .map(
        row => `
          ${row
            .map(k =>
              k === null
                ? '<div class="key none"></div>'
                : `<div class="key">${k}</div>`
            )
            .join('')}
        `
      )

    return `
      <div class="layer">
        <div class="name">
          ${i}
        </div>
        <div class="keymap">
          ${rows.join('')}
        </div>
      </div>
    `
  })
  .join('')

const html = `
<style>
  :root {
    --space: 8px;
    --brown: 166, 146, 129;
    --black: 88, 88, 88;
    --white: 255, 255, 255;
  }
  body {
    margin: 0;
  }
  .layer {
    margin: 0px;
    width: calc(60px * 14 + var(--space) * 2);
    position: relative;
  }
  .name {
    position: absolute;
    top: 18px;
    left: 50%;
    transform: translateX(-50%);
    display: flex;
    justify-content: center;
    font-size: 1.75rem;
    line-height: 2;
    color: rgba(var(--black), 0.6);
  }
  .keymap {
    background-color: rgb(240, 238, 235);
    /* box-shadow: rgba(0, 0, 0, 0.12) 0px 1px 10px; */
    font-family: Monoid;
    font-size: 12px;
    /* border-radius: 4px; */
    padding: 8px;
    display: flex;
    flex-direction: row;
    flex-wrap: wrap;
  }
  .key {
    width: 56px;
    height: 22px;
    border-radius: 2px;
    display: flex;
    justify-content: center;
    align-items: center;
    background-color: transparent;
    margin: 2px;
  }
  .key:not(.none) {
    background-color: rgb(var(--white));
    box-shadow: 0 0.5px 3px rgba(var(--white), 1);
    color: var(--black);
  }
  ${[1, 14, 17, 18, 25, 26, 33, 38, 43, 49, 50, 56, 60, 63, 64, 67]
    .map(n => `.key:nth-child(${n})`)
    .join()} {
    background-color: rgb(var(--black));
    box-shadow: 0 0.5px 3px rgba(var(--black), 0.5);
    color: rgb(var(--white));
  }
</style>

${mapsString}
`

fs.writeFileSync(__dirname + '/keymap.html', html)
