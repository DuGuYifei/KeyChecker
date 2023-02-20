import {
	createRouter,
	createWebHashHistory,
	createWebHistory
} from "vue-router"

const routes = [
	{
		path: '',
		name: 'rootManager',
		component: () => import('../views/keys/key_list.vue')
	},
]

const router = createRouter({
	history: createWebHistory(),
	routes
})

export default router