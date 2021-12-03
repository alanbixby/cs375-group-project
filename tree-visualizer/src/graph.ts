import PrettyBT from './pbt'
import { createCanvas } from 'canvas'
import fs from 'fs'

enum Color {
  RED,
  BLACK,
  DEFAULT
}

interface cppJson<T> {
  parent?: T,
  left?: T,
  right?: T,
  value?: T,
  color?: Color,
  disabled?: boolean,
  id: T
}

interface btNode<T> {
  left?: T | btNode<T>,
  right?: T | btNode<T>,
  val: T,
  id: T,
  color: Color,
  disabled?: boolean,
}

function nodeToStr<T>(tree: btNode<T>[], key?: T) {
  const node = tree.find(elem => elem.val == key)
  if (!node) {
    return
  }
  let retVal: btNode<T> = { val: node.val, color: node.color, disabled: node.disabled, id: node.id }
  if (node.right) {
    // @ts-ignore
    retVal.right = nodeToStr(tree, node.right)
  }
  if (node.left) {
    // @ts-ignore
    retVal.left = nodeToStr(tree, node.left)
  }
  return retVal;
}

export default function draw<T>() {
  const json: cppJson<T>[] = JSON.parse(fs.readFileSync('src/treeBuild.json', { encoding: "utf-8" }))

  let root = json.find(node => !node.parent)

  //@ts-ignore
  const renamed: btNode<T>[] = json.map((node) => {
    return {
      id: node.value,
      val: node.id,
      left: node.left,
      right: node.right,
      color: node.color,
      disabled: node.disabled
    }
  })

  let tree = nodeToStr(renamed, root?.id)

  const canvas = createCanvas(1800, 800)
  PrettyBT.drawBinaryTree(canvas, { ...tree }, 30);

  return canvas;
}