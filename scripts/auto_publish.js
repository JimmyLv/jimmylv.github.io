const fs = require('fs')
const jsyaml = require('js-yaml')
const nightmare = require('./nightmare')

const readFile = (path) => fs.readFileSync(path, { encoding: 'utf-8' })

const config = jsyaml.load(readFile('scripts/config.yml'))
const result = readFile('source/_posts/2016-09-16-sorting-out-knowledge-from-information.md').split('---')
const article = {
  meta: jsyaml.load(result[1]),
  content: result.slice(2).join('---')
}

const { jianshu, zhihu, segmentfault } = config.accounts

require('./jianshu')(nightmare, jianshu, article)
require('./segmentfault')(nightmare, segmentfault, article)
