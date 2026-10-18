public class DoubleLinkedList<T> {
	class Node<U> {
		U data;
		Node<U> pred, succ;
		Node (U data, Node<U> pred, Node<U> succ){
			this.data = data;
			this.pred = pred;
			this.succ = succ;
		}
	}
	Node<T> head, tail;
	
	DoubleLinkedList (){
		head = new Node<T>(null, null, null);
		tail = new Node<T>(null, null, null);
		head.pred = null;
		head.succ = tail;
		tail.pred = head;
		tail.succ = null;
	}
}
