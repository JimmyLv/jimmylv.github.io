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

console.log(article)

nightmare
  .goto('http://www.jianshu.com/sign_in')
  .viewport(1024, 768)
  .insert('#sign_in_name', '460051518@qq.com')
  .insert('#sign_in_password', 'xx')
  .wait('.gt_ajax_tip.success')
  .click('button.ladda-button.submit-button')
  .wait('a.btn.btn-large.btn-success')
  .click('a.btn.btn-large.btn-success')
  .wait('#note_title')
  .insert('#note_title', '') // clear
  .insert('#note_title', article.meta.title)
  .insert('textarea.text.mousetrap', '') // clear
  .insert('textarea.text.mousetrap', article.content)
  .click('#publish-button')
  .evaluate(() => {
    /* eslint-disable */
    // location.reload()
    // location.href = 'http://www.jianshu.com/writer#/'
    function handle() {
      // do something...
      console.info(document.title)
    }
    
    setInterval(handle, 2000)
    return document.title
    /* eslint-enable */
  })
  .then(res => console.info(res))
  .catch(err => console.error(err))