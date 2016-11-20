const fs = require('fs')
const Nightmare = require('nightmare')
const jsyaml = require('js-yaml')

const options = {
  openDevTools: {
    mode: 'bottom',       // 开发者工具位置：right, bottom, undocked, detach
  },
  show: true,                 // 要不要显示浏览器
  dock: false,                 // 要不要在Dock上显示图标
  typeInterval: 20,            // .type() 方法超时时长，单位:ms (default: 100ms)
  waitTimeout: 60000,         // .wait() 方法超时时长，单位:ms (default: 30s)
  executionTimeout: 86400000, // .evaluate() 方法超时时长，单位:ms (default: 30s)
}

const nightmare = new Nightmare(options)

const content = fs.readFileSync('source/_posts/hello-world.md', { encoding: 'utf-8' })
const result = content.split('---')
const article = {
  meta: jsyaml.load(result[1]),
  content: result.slice(2).join('---')
}

const config = jsyaml.load(fs.readFileSync('scripts/config.yml', { encoding: 'utf-8' }))

console.log(config)

const account = config.accounts.jianshu

nightmare
  .goto('http://www.jianshu.com/')
  .exists('.user.avatar') // already login?
  .then(isLogin => {
    console.info('already login?', isLogin)
    if (!isLogin) {
      nightmare
        .goto('http://www.jianshu.com/sign_in')
        .insert('#sign_in_name', account.username)
        .insert('#sign_in_password', account.password)
        .wait('.gt_ajax_tip.success')
        .click('button.ladda-button.submit-button')
    }
    nightmare
      .wait('a.btn.btn-large.btn-success')
      .click('a.btn.btn-large.btn-success')
      .wait('a.new-note-link')
      .click('a.new-note-link')
      .wait(1500) // waiting to create new note otherwise will override original article
      .wait('#note_title')
      .insert('#note_title', article.meta.title)
      .insert('textarea.text.mousetrap', article.content)
      .wait(1500) // publish button will hidden when saving draft
      .wait('#publish-button')
      .click('#publish-button')
      .wait(3000) // publish need some times
      .evaluate(() => {
        /* eslint-disable */
        const success = $('h3:contains("文章发布成功")')[0]
        if (success) {
          const title = $('.text-info')[0]
          console.info('文章发布成功', title)
          return `[${title.text}](${title.href})`
        }
        
        throw new Error('文章发布异常')
        /* eslint-enable */
      })
      .end()
      .then(title => console.log(`${title} => 发布成功`))
      .catch(err => console.error(err))
  })


// update article need find a.note-link.title text() === article.

// eg: $( "a:contains('Hello World')" )