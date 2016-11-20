const TAGS = require('./tags.json')

const TIMES_TO_DELAY = 2000 // need decrease/increase deps on network.

function publish(nightmare, { username, password }, { meta, content }) {
  nightmare
    .goto('https://segmentfault.com/write')
    .exists('.user-avatar') // already login?
    .then(isLogin => {
      console.info('already login?', isLogin)
      if (!isLogin) {
        nightmare
          .click('a.SFLogin')
          .wait('h1.h4.text-muted.login-title')
          .insert('input[name="username"]', username)
          .insert('input[name="password"]', password)
          .click('button.btn.btn-primary.pull-right.pl20.pr20')
      }
      // will redirect to write page directly
      nightmare
        .wait('#myTitle')
        .insert('#myTitle', meta.title)
        .insert('textarea#myEditor', content)
        .evaluate(() => $('input.tagsInput').removeClass('hidden'))
        .then(
          nightmare
            .insert('input.tagsInput', TAGS['开发语言'][0].id) // javascript
            .click('#publishIt')
            .wait(TIMES_TO_DELAY) // publish need some times
            .url()
            .then(url => {
                if (url === 'https://segmentfault.com/write') {
                  throw new Error('文章发布异常...')
                }
                console.info(`发布成功 => [${meta.title}](${url})`)
                return nightmare.end()
              }
            )
            .catch(err => console.error(err))
        )
    })
}

module.exports = publish
