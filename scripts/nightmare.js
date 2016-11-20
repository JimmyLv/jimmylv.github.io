const Nightmare = require('nightmare')

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

module.exports = new Nightmare(options)
